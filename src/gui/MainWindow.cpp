// src/gui/MainWindow.cpp
#include "MainWindow.h"
#include "core/ClipboardManager.h"

// Include all necessary Qt headers for our UI elements and functionality
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFont>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug> // For warning messages

MainWindow::MainWindow(ClipboardManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager) {
    
    // --- Load resources FIRST ---
    // The ':/' prefix tells Qt to look inside the embedded resources (.qrc file)
    setWindowIcon(QIcon(":/app_icon.ico")); 
    loadStyleSheet();

    // --- Setup UI with a professional layout ---
    setWindowTitle("ClipSync Pro");
    setMinimumSize(450, 600);

    // Main vertical layout for the whole window
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15); // A bit more padding

    // Header with a bold title
    QLabel* titleLabel = new QLabel("Clipboard History");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    
    // Search Bar for filtering history
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search history...");
    m_searchBar->setFixedHeight(35); // A comfortable height for typing
    m_searchBar->setClearButtonEnabled(true); // Adds a small 'x' to clear the search

    // History List where items will be displayed
    m_historyListWidget = new QListWidget();
    m_historyListWidget->setWordWrap(true); // Long items will wrap to the next line

    // Bottom layout for the "Clear History" button
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    QPushButton* clearButton = new QPushButton("Clear History");
    bottomLayout->addStretch(); // Pushes the button to the right side of the window
    bottomLayout->addWidget(clearButton);

    // Add all the widgets we created to the main layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_searchBar);
    mainLayout->addWidget(m_historyListWidget, 1); // The '1' is a "stretch factor" that makes the list expand to fill available space
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);

    // --- Connect Signals and Slots (The logic that makes the UI interactive) ---

    // When the core manager has new data, it tells the UI to update
    connect(m_manager, &ClipboardManager::historyChanged, this, &MainWindow::updateFullHistory);
    connect(m_manager, &ClipboardManager::newItemAdded, this, &MainWindow::addItemToList);

    // When the user interacts with UI elements, we call our handler functions
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(m_historyListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(m_searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchQueryChanged);
}

/**
 * @brief Loads the stylesheet from the embedded Qt resources.
 */
void MainWindow::loadStyleSheet() {
    // The path ':/src/res/style.qss' corresponds to the path in our resources.qrc file.
    QFile styleFile(":/src/res/style.qss"); 
    if (!styleFile.open(QFile::ReadOnly | QFile::Text)) {
        qWarning("Could not open stylesheet from resources.");
        return;
    }
    this->setStyleSheet(styleFile.readAll());
}

/**
 * @brief This slot is called every time the user types in the search bar.
 * It filters the visible items in the list.
 */
void MainWindow::onSearchQueryChanged(const QString& text) {
    // Loop through all items in the list
    for (int i = 0; i < m_historyListWidget->count(); ++i) {
        QListWidgetItem* item = m_historyListWidget->item(i);
        // Hide or show the item based on whether it contains the search text.
        // Qt::CaseInsensitive makes the search work for both "Hello" and "hello".
        const bool matches = item->text().contains(text, Qt::CaseInsensitive);
        item->setHidden(!matches);
    }
}

/**
 * @brief Called when the application is closing. Ensures the history is saved.
 */
void MainWindow::closeEvent(QCloseEvent* event) {
    m_manager->saveOnExit();
    event->accept(); // Allows the window to close
}

/**
 * @brief This slot clears the entire list and repopulates it.
 * Used for initial load or after a full clear.
 */
void MainWindow::updateFullHistory(const QStringList& history) {
    m_historyListWidget->clear();
    m_historyListWidget->addItems(history);
    // After updating, re-apply the current search filter in case there was text in the bar
    onSearchQueryChanged(m_searchBar->text());
}

/**
 * @brief This slot adds a single new item to the top of the list.
 */
void MainWindow::addItemToList(const QString& item) {
    m_historyListWidget->insertItem(0, item);
    // After adding, check if it should be visible based on the current search filter
    onSearchQueryChanged(m_searchBar->text());
}

/**
 * @brief Called when the "Clear History" button is clicked.
 */
void MainWindow::onClearButtonClicked() {
    // Show a confirmation dialog to prevent accidental deletion
    if (QMessageBox::question(this, "Confirm Clear", "Are you sure you want to clear your entire clipboard history?") == QMessageBox::Yes) {
        m_manager->clearHistory();
    }
}

/**
 * @brief Called when an item in the list is double-clicked by the user.
 */
void MainWindow::onItemDoubleClicked(QListWidgetItem* item) {
    if (!item) return; // Safety check

    // Get the text from the item and tell the manager to copy it
    m_manager->copyToClipboardByText(item->text());
    
    // Show a temporary "Copied!" message to the user
    QMessageBox* msgBox = new QMessageBox(
        QMessageBox::Information,
        "Copied!",
        "The selected item has been copied to your clipboard.",
        QMessageBox::NoButton,
        this
    );

    // **** THIS IS THE CORRECTED LINE ****
    msgBox->setStandardButtons(QMessageBox::NoButton); 
    
    // Make the message box close itself after 1 second (1000 ms)
    QTimer::singleShot(1000, msgBox, &QMessageBox::accept);
    msgBox->exec();
}