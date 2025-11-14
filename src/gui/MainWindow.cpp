// src/gui/MainWindow.cpp
#include "MainWindow.h"
#include "core/ClipboardManager.h"
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
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(ClipboardManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager) {
    
    // We get the application's directory path
    QString appPath = QApplication::applicationDirPath();
    
    // Load the icon directly from the file system
    setWindowIcon(QIcon(appPath + "/assets/ico.ico")); 
    
    // Load the stylesheet directly from the file system
    loadStyleSheet(appPath + "/res/style.qss");

    setWindowTitle("ClipSync Pro");
    setMinimumSize(450, 600);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    QLabel* titleLabel = new QLabel("Clipboard History");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search history...");
    m_searchBar->setFixedHeight(35);
    m_searchBar->setClearButtonEnabled(true);
    m_historyListWidget = new QListWidget();
    m_historyListWidget->setWordWrap(true);
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    QPushButton* clearButton = new QPushButton("Clear History");
    bottomLayout->addStretch();
    bottomLayout->addWidget(clearButton);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_searchBar);
    mainLayout->addWidget(m_historyListWidget, 1);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
    connect(m_manager, &ClipboardManager::historyChanged, this, &MainWindow::updateFullHistory);
    connect(m_manager, &ClipboardManager::newItemAdded, this, &MainWindow::addItemToList);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(m_historyListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(m_searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchQueryChanged);
}

void MainWindow::loadStyleSheet(const QString& path) {
    QFile styleFile(path); 
    if (!styleFile.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Could not open stylesheet file at:" << path;
        return;
    }
    this->setStyleSheet(styleFile.readAll());
}

// ... THE REST OF THE FILE IS THE SAME AS BEFORE ...

void MainWindow::onSearchQueryChanged(const QString& text) {
    for (int i = 0; i < m_historyListWidget->count(); ++i) {
        QListWidgetItem* item = m_historyListWidget->item(i);
        const bool matches = item->text().contains(text, Qt::CaseInsensitive);
        item->setHidden(!matches);
    }
}
void MainWindow::closeEvent(QCloseEvent* event) {
    if (QApplication::quitOnLastWindowClosed()) {
        hide();
        event->ignore();
    } else {
        event->accept();
    }
}
void MainWindow::updateFullHistory(const QStringList& history) {
    m_historyListWidget->clear();
    m_historyListWidget->addItems(history);
    onSearchQueryChanged(m_searchBar->text());
}
void MainWindow::addItemToList(const QString& item) {
    m_historyListWidget->insertItem(0, item);
    onSearchQueryChanged(m_searchBar->text());
}
void MainWindow::onClearButtonClicked() {
    if (QMessageBox::question(this, "Confirm Clear", "Are you sure you want to clear your entire clipboard history?") == QMessageBox::Yes) {
        m_manager->clearHistory();
    }
}
void MainWindow::onItemDoubleClicked(QListWidgetItem* item) {
    if (!item) return;
    m_manager->copyToClipboardByText(item->text());
    QMessageBox* msgBox = new QMessageBox(QMessageBox::Information,"Copied!","The selected item has been copied to your clipboard.",QMessageBox::NoButton,this);
    msgBox->setStandardButtons(QMessageBox::NoButton); 
    QTimer::singleShot(1000, msgBox, &QMessageBox::accept);
    msgBox->exec();
}