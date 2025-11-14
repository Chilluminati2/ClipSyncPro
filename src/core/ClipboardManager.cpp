// src/core/ClipboardManager.cpp
#include "ClipboardManager.h"
#include "storage/HistoryManager.h"
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>

ClipboardManager::ClipboardManager(HistoryManager* historyManager, QObject* parent)
    : QObject(parent), m_clipboard(QApplication::clipboard()), m_historyManager(historyManager) {}

void ClipboardManager::initialize() {
    m_history = m_historyManager->loadHistory();
    emit historyChanged(m_history);

    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
}

const QStringList& ClipboardManager::getHistory() const {
    return m_history;
}

void ClipboardManager::clearHistory() {
    m_history.clear();
    emit historyChanged(m_history);
    qDebug() << "Clipboard manager history cleared.";
}

void ClipboardManager::copyToClipboardByText(const QString& text) {
    disconnect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
    m_clipboard->setText(text);
    connect(m_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::onClipboardDataChanged);
}

void ClipboardManager::saveOnExit() {
    m_historyManager->saveHistory(m_history);
}

void ClipboardManager::onClipboardDataChanged() {
    if (!m_clipboard->mimeData()->hasText()) return;

    QString newText = m_clipboard->text();

    if (newText.isEmpty() || (!m_history.isEmpty() && m_history.first() == newText)) {
        return;
    }

    m_history.prepend(newText);
    emit newItemAdded(newText);
    qDebug() << "New item captured:" << newText;
}