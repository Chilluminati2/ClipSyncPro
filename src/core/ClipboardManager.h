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

public slots:
    void clearHistory();
    void copyToClipboard(const QVariant& data);
    void saveOnExit();

// **** THIS IS THE FIX ****
signals:
    // We are now declaring that this class can emit a signal named 'historyChanged'.
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