// src/core/ClipboardManager.h
#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QStringList>

class QClipboard;
class HistoryManager;

class ClipboardManager : public QObject {
    Q_OBJECT

public:
    explicit ClipboardManager(HistoryManager* historyManager, QObject* parent = nullptr);
    void initialize();
    const QStringList& getHistory() const;

public slots:
    void clearHistory();
    void copyToClipboardByText(const QString& text);
    void saveOnExit();

private slots:
    void onClipboardDataChanged();

signals:
    void historyChanged(const QStringList& history);
    void newItemAdded(const QString& item);

private:
    QClipboard* m_clipboard;
    HistoryManager* m_historyManager;
    QStringList m_history;
};

#endif // CLIPBOARDMANAGER_H