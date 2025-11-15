// src/core/ClipboardManager.h
#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QMimeData>
#include "Snippet.h"

class QClipboard;
class HistoryManager;

class ClipboardManager : public QObject {
    Q_OBJECT

public:
    explicit ClipboardManager(HistoryManager* historyManager, QObject* parent = nullptr);
    void initialize();
    const QList<Snippet>& getHistory() const;
    void saveHistory(); // New public save function

public slots:
    void clearHistory();
    void copyToClipboard(const QVariant& data);
    // The saveOnExit slot is no longer needed and has been removed.

signals:
    void historyChanged(const QList<Snippet>& history);

private slots:
    void onClipboardDataChanged();

private:
    Snippet createSnippetFromMimeData(const QMimeData* mimeData);
    bool isDuplicate(const Snippet& newSnippet);

    QClipboard* m_clipboard;
    HistoryManager* m_historyManager;
    QList<Snippet> m_history;
};

#endif // CLIPBOARDMANAGER_H