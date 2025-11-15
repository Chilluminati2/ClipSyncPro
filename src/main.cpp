// src/main.cpp
#include <QApplication>
#include <QPalette>
#include <QColor>
#include <QStyleFactory>

#include "gui/MainWindow.h"
#include "gui/SystemTray.h"
#include "platform/GlobalHotkey.h"
#include "core/ClipboardManager.h"
#include "storage/HistoryManager.h"
#include "core/Snippet.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qRegisterMetaType<Snippet>();
    
    // --- SIMPLE, RELIABLE DARK THEME ---
    // Use the "Fusion" style for a consistent look across platforms
    app.setStyle(QStyleFactory::create("Fusion"));

    // Create a dark color palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(45, 45, 45)); // Main window background
    darkPalette.setColor(QPalette::WindowText, Qt::white); // Main text color
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35)); // Background for text inputs, lists
    darkPalette.setColor(QPalette::AlternateBase, QColor(45, 45, 45)); // Alternating row colors
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::black);
    darkPalette.setColor(QPalette::Text, Qt::white); // Text color for inputs, lists
    darkPalette.setColor(QPalette::Button, QColor(60, 60, 60)); // Button background
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // Color for selected items
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    
    // Apply the dark palette to the entire application
    app.setPalette(darkPalette);
    
    // The rest of the setup is the same
    app.setQuitOnLastWindowClosed(false);
    app.setOrganizationName("YourCompany");
    app.setApplicationName("ClipSyncPro");

    HistoryManager historyManager;
    ClipboardManager clipboardManager(&historyManager);
    MainWindow window(&clipboardManager);
    SystemTray tray(&window);
    tray.show();

    GlobalHotkey hotkey;
    app.installNativeEventFilter(&hotkey);
    QObject::connect(&hotkey, &GlobalHotkey::activated, &window, &MainWindow::toggleVisibility);
    QObject::connect(&app, &QApplication::aboutToQuit, &clipboardManager, &ClipboardManager::saveOnExit);

    clipboardManager.initialize();
    window.show();

    return app.exec();
}