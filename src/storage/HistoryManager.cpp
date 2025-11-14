// src/storage/HistoryManager.cpp
#include "HistoryManager.h"
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStandardPaths>
#include <QDebug>
#include <QFileInfo>

HistoryManager::HistoryManager() {
    m_savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/clipboard_history.json";
    qDebug() << "History file path:" << m_savePath;

    // Ensure the directory for the save file exists
    QFileInfo fileInfo(m_savePath);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

void HistoryManager::saveHistory(const QStringList& history) const {
    QJsonArray historyArray;
    for (const QString &item : history) {
        historyArray.append(item);
    }
    
    QJsonDocument doc(historyArray);
    QFile saveFile(m_savePath);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open save file for writing:" << m_savePath;
        return;
    }

    saveFile.write(doc.toJson());
    qDebug() << "History saved successfully.";
}

QStringList HistoryManager::loadHistory() const {
    QFile loadFile(m_savePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open save file for reading. Starting fresh.";
        return QStringList();
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonArray historyArray = loadDoc.array();

    QStringList history;
    for (const QJsonValue &value : historyArray) {
        history.append(value.toString());
    }

    qDebug() << "History loaded successfully. Items:" << history.size();
    return history;
}