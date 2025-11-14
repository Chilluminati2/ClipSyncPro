// src/gui/MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QListWidget;
class QListWidgetItem;
class QLineEdit;
class ClipboardManager;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(ClipboardManager* manager, QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void updateFullHistory(const QStringList& history);
    void addItemToList(const QString& item);
    void onClearButtonClicked();
    void onItemDoubleClicked(QListWidgetItem* item);
    void onSearchQueryChanged(const QString& text);

private:
    void loadStyleSheet();

    // UI Elements
    QListWidget* m_historyListWidget;
    QLineEdit* m_searchBar;
    ClipboardManager* m_manager;
};

#endif // MAINWINDOW_H