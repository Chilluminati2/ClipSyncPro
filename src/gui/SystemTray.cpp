// src/gui/SystemTray.cpp
#include "SystemTray.h"
#include <QMenu>
#include <QApplication>
#include <QIcon>
#include <QWidget>

SystemTray::SystemTray(QWidget* parent) : QObject(parent), m_parentWindow(parent) {
    // We get the application's directory path
    QString appPath = QApplication::applicationDirPath();
    
    // Load the icon directly from the file system
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setIcon(QIcon(appPath + "/assets/ico.ico"));
    m_trayIcon->setToolTip("ClipSync Pro");

    createMenu();

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &SystemTray::onIconActivated);
}

void SystemTray::show() {
    m_trayIcon->show();
}

void SystemTray::createMenu() {
    m_trayMenu = new QMenu();
    QAction* toggleVisibilityAction = new QAction("Show/Hide ClipSync Pro", this);
    connect(toggleVisibilityAction, &QAction::triggered, [this]() {
        m_parentWindow->setVisible(!m_parentWindow->isVisible());
        if (m_parentWindow->isVisible()) {
            m_parentWindow->activateWindow();
        }
    });
    QAction* quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    m_trayMenu->addAction(toggleVisibilityAction);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(quitAction);
    m_trayIcon->setContextMenu(m_trayMenu);
}

void SystemTray::onIconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::DoubleClick) {
        m_parentWindow->setVisible(!m_parentWindow->isVisible());
        if (m_parentWindow->isVisible()) {
            m_parentWindow->activateWindow();
        }
    }
}