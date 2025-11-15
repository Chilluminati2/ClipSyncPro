// src/storage/HistoryManager.h
#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QList> // Changed from QStringList
#include "core/Snippet.h" // Include Snippet

class HistoryManager {
public:
    HistoryManager();
    void saveHistory(const QList<Snippet>& history) const;
    QList<Snippet> loadHistory() const;

private:
    QString m_savePath;
    QString m_imagePath; // A dedicated folder to save image files
};

#endif // HISTORYMANAGER_H