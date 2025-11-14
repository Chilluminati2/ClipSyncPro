#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

// Forward declarations
class QListWidget;
class QListWidgetItem;
class QLineEdit;
class ClipboardManager;
class QString; // Added for the function argument

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
    // **** THIS IS THE FIX ****
    // We are telling the blueprint that this function now takes a path as an argument.
    void loadStyleSheet(const QString& path);

    // UI Elements
    QListWidget* m_historyListWidget;
    QLineEdit* m_searchBar;
    ClipboardManager* m_manager;
};

#endif // MAINWINDOW_H