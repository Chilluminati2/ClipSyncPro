// src/storage/HistoryManager.h
#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QStringList>

class HistoryManager {
public:
    HistoryManager();
    void saveHistory(const QStringList& history) const;
    QStringList loadHistory() const;

private:
    QString m_savePath;
};

#endif // HISTORYMANAGER_H