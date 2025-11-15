// src/core/ClipboardManager.cpp
#include "ClipboardManager.h"
#include "storage/HistoryManager.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDateTime>
#include <QImage>
#include <QColor>
#include <QRegularExpression>
#include <QDebug>

ClipboardManager::ClipboardManager(HistoryManager* historyManager, QObject* parent)
    : QObject(parent), m_clipboard(QApplication::clipboard()), m_historyManager(historyManager) {}

void ClipboardManager::initialize() {
    m_history = m_historyManager->loadHistory();
    emit historyChanged(m_history);
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
}

const QList<Snippet>& ClipboardManager::getHistory() const {
    return m_history;
}

void ClipboardManager::clearHistory() {
    m_history.clear();
    emit historyChanged(m_history);
}

void ClipboardManager::copyToClipboard(const QVariant& data) {
    disconnect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
    
    if (data.canConvert<QImage>()) {
        m_clipboard->setImage(data.value<QImage>());
    } else {
        m_clipboard->setText(data.toString());
    }

    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
}

void ClipboardManager::saveOnExit() {
    m_historyManager->saveHistory(m_history);
}

void ClipboardManager::onClipboardDataChanged() {
    const QMimeData* mimeData = m_clipboard->mimeData();
    if (!mimeData) return;

    Snippet newSnippet = createSnippetFromMimeData(mimeData);
    
    // Check for empty or duplicate snippets
    if (newSnippet.data.isNull() || isDuplicate(newSnippet)) {
        return;
    }

    m_history.prepend(newSnippet);
    qDebug() << "New snippet captured:" << newSnippet.displayText;
    emit historyChanged(m_history);
}

bool ClipboardManager::isDuplicate(const Snippet& newSnippet) {
    if (m_history.isEmpty()) return false;

    const Snippet& lastSnippet = m_history.first();
    if (newSnippet.type != lastSnippet.type) return false;

    if (newSnippet.type == Snippet::Text) {
        return newSnippet.data.toString() == lastSnippet.data.toString();
    }
    if (newSnippet.type == Snippet::Image) {
        // Simple comparison for now. A more robust check might use hashes.
        return newSnippet.data.value<QImage>() == lastSnippet.data.value<QImage>();
    }
    return false;
}

Snippet ClipboardManager::createSnippetFromMimeData(const QMimeData* mimeData) {
    Snippet snippet;
    snippet.timestamp = QDateTime::currentDateTime();

    // Prioritize Images over Text
    if (mimeData->hasImage()) {
        snippet.type = Snippet::Image;
        QImage image = qvariant_cast<QImage>(mimeData->imageData());
        snippet.data = image; // Store the full image
        snippet.displayText = QString("[Image] %1x%2 - Copied at %3")
                                .arg(image.width()).arg(image.height())
                                .arg(snippet.timestamp.toString("h:mm:ss ap"));
    }
    // Then check for Text
    else if (mimeData->hasText()) {
        snippet.type = Snippet::Text;
        QString text = mimeData->text();
        snippet.data = text;
        snippet.displayText = text.simplified(); // Show a cleaned-up version

        // --- CONTENT-AWARE LOGIC ---
        // Check for Hex/RGB color codes
        QRegularExpression colorRegex("(#[0-9a-fA-F]{3,8}|rgb[a]?\\s*\\([0-9, ]+\\))");
        QRegularExpressionMatch match = colorRegex.match(text.trimmed());
        if (match.hasMatch()) {
            QColor color(match.captured(1));
            if (color.isValid()) {
                snippet.previewColor = color;
                snippet.displayText = QString("[Color] %1").arg(match.captured(1));
            }
        }
        // Check for URLs
        else if (text.trimmed().startsWith("http://") || text.trimmed().startsWith("https://")) {
            snippet.displayText = QString("[Link] %1").arg(text.trimmed());
        }
    }
    
    return snippet;
}