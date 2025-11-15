// src/gui/MainWindow.cpp
#include "MainWindow.h"
#include "core/ClipboardManager.h"
#include "gui/SnippetDelegate.h"
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFont>
#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>

Q_DECLARE_METATYPE(Snippet)

MainWindow::MainWindow(ClipboardManager* manager, QWidget* parent)
    : QWidget(parent), m_manager(manager) {
    
    // We go back to a simple window with a normal title bar
    setWindowIcon(QIcon(":/app_icon.ico"));
    setWindowTitle("ClipSync Pro");
    setMinimumSize(500, 600);

    // Apply minimal stylesheet for things the palette doesn't control well, like scrollbars
    applyStylesheet();

    // Main layout with standard margins
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);
    
    // UI elements
    m_searchBar = new QLineEdit();
    m_searchBar->setPlaceholderText("Search history...");
    m_searchBar->setFixedHeight(35);

    m_historyView = new QListView();
    m_model = new QStandardItemModel(this);
    m_historyView->setModel(m_model);
    m_historyView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_historyView->setItemDelegate(new SnippetDelegate(this));
    m_historyView->setWordWrap(true);

    QHBoxLayout* bottomLayout = new QHBoxLayout();
    QLabel* footerLabel = new QLabel("Created by Kareem with love ❤️");
    footerLabel->setObjectName("FooterLabel"); // In case we want to style it
    QPushButton* clearButton = new QPushButton("Clear History");
    bottomLayout->addWidget(footerLabel);
    bottomLayout->addStretch();
    bottomLayout->addWidget(clearButton);

    // Add widgets to the layout
    mainLayout->addWidget(m_searchBar);
    mainLayout->addWidget(m_historyView, 1);
    mainLayout->addLayout(bottomLayout);
    
    // Connect signals
    connect(m_manager, &ClipboardManager::historyChanged, this, &MainWindow::updateHistoryView);
    connect(clearButton, &QPushButton::clicked, m_manager, &ClipboardManager::clearHistory);
    connect(m_historyView, &QListView::doubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(m_searchBar, &QLineEdit::textChanged, this, &MainWindow::onSearchQueryChanged);
}

void MainWindow::applyStylesheet() {
    // A minimal stylesheet just for the scrollbar and footer
    this->setStyleSheet(
        "QScrollBar:vertical { border: none; background: #232323; width: 10px; margin: 0; }"
        "QScrollBar::handle:vertical { background-color: #505050; min-height: 20px; border-radius: 5px; }"
        "QScrollBar::handle:vertical:hover { background-color: #606060; }"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical { height: 0px; }"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; }"
        "#FooterLabel { color: #888; font-size: 9pt; }"
    );
}

void MainWindow::toggleVisibility() {
    if (isMinimized()) {
        showNormal();
    }
    
    if (isVisible()) {
        hide();
    } else {
        show();
        activateWindow();
        raise();
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

void MainWindow::updateHistoryView(const QList<Snippet>& history) {
    m_model->clear();
    for (const Snippet& snippet : history) {
        QStandardItem* item = new QStandardItem();
        item->setData(QVariant::fromValue(snippet), Qt::UserRole);
        m_model->appendRow(item);
    }
    onSearchQueryChanged(m_searchBar->text());
}

void MainWindow::onItemDoubleClicked(const QModelIndex& index) {
    if (!index.isValid()) return;
    Snippet snippet = index.data(Qt::UserRole).value<Snippet>();
    m_manager->copyToClipboard(snippet.data);
    hide();
}

void MainWindow::onSearchQueryChanged(const QString& text) {
    for (int i = 0; i < m_model->rowCount(); ++i) {
        QModelIndex index = m_model->index(i, 0);
        Snippet snippet = index.data(Qt::UserRole).value<Snippet>();
        bool matches = snippet.displayText.contains(text, Qt::CaseInsensitive);
        m_historyView->setRowHidden(i, !matches);
    }
}