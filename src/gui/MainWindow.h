// src/gui/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "core/Snippet.h"

// Forward declarations
class QListView;
class QLineEdit;
class QStandardItemModel;
class ClipboardManager;
class QModelIndex;
class QCloseEvent;

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(ClipboardManager* manager, QWidget* parent = nullptr);
    void toggleVisibility();

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void updateHistoryView(const QList<Snippet>& history);
    void onItemDoubleClicked(const QModelIndex& index);
    void onSearchQueryChanged(const QString& text);

private:
    void applyStylesheet();

    // UI Elements
    QListView* m_historyView;
    QLineEdit* m_searchBar;
    QStandardItemModel* m_model;
    ClipboardManager* m_manager;
};

#endif // MAINWINDOW_H