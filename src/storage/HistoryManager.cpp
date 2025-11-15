// src/storage/HistoryManager.cpp
#include "HistoryManager.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QBuffer> // For converting images to data
#include <QImage>
#include <QDebug>
#include <QFileInfo>

HistoryManager::HistoryManager() {
    QString appDataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    m_savePath = appDataLocation + "/history.json";
    m_imagePath = appDataLocation + "/images/";

    // Ensure the directories for the save file and images exist
    QDir dir;
    dir.mkpath(m_imagePath);
}

void HistoryManager::saveHistory(const QList<Snippet>& history) const {
    QJsonArray historyArray;
    for (const Snippet &snippet : history) {
        QJsonObject snippetObj;
        snippetObj["timestamp"] = snippet.timestamp.toString(Qt::ISODate);
        snippetObj["type"] = snippet.type;

        if (snippet.type == Snippet::Text) {
            snippetObj["data"] = snippet.data.toString();
        } else if (snippet.type == Snippet::Image) {
            // For images, save them as files and store the filename in the JSON
            QImage image = snippet.data.value<QImage>();
            QString filename = QString("img_%1.png").arg(snippet.timestamp.toMSecsSinceEpoch());
            QString fullPath = m_imagePath + filename;
            if (image.save(fullPath, "PNG")) {
                snippetObj["data"] = filename;
            }
        }
        historyArray.append(snippetObj);
    }
    
    QJsonDocument doc(historyArray);
    QFile saveFile(m_savePath);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open save file for writing:" << m_savePath;
        return;
    }
    saveFile.write(doc.toJson());
}

QList<Snippet> HistoryManager::loadHistory() const {
    QList<Snippet> history;
    QFile loadFile(m_savePath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        return history;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonArray historyArray = loadDoc.array();

    for (const QJsonValue &value : historyArray) {
        QJsonObject snippetObj = value.toObject();
        Snippet snippet;
        snippet.timestamp = QDateTime::fromString(snippetObj["timestamp"].toString(), Qt::ISODate);
        snippet.type = static_cast<Snippet::Type>(snippetObj["type"].toInt());

        if (snippet.type == Snippet::Text) {
            QString text = snippetObj["data"].toString();
            snippet.data = text;
            snippet.displayText = text.simplified();

            // Re-run content-aware logic on load
            QRegularExpression colorRegex("(#[0-9a-fA-F]{3,8}|rgb[a]?\\s*\\([0-9, ]+\\))");
            QRegularExpressionMatch match = colorRegex.match(text.trimmed());
            if (match.hasMatch() && QColor(match.captured(1)).isValid()) {
                snippet.previewColor = QColor(match.captured(1));
                snippet.displayText = QString("[Color] %1").arg(match.captured(1));
            } else if (text.trimmed().startsWith("http")) {
                snippet.displayText = QString("[Link] %1").arg(text.trimmed());
            }

        } else if (snippet.type == Snippet::Image) {
            QString filename = snippetObj["data"].toString();
            QString fullPath = m_imagePath + filename;
            QImage image(fullPath);
            if (!image.isNull()) {
                snippet.data = image;
                snippet.displayText = QString("[Image] %1x%2 - Copied at %3")
                                        .arg(image.width()).arg(image.height())
                                        .arg(snippet.timestamp.toString("h:mm:ss ap"));
            }
        }
        history.append(snippet);
    }
    return history;
}