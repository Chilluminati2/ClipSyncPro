// src/main.cpp
#include <QApplication>
#include <QObject>

#include "gui/MainWindow.h"
#include "gui/SystemTray.h"
#include "platform/GlobalHotkey.h"
#include "core/ClipboardManager.h"
#include "storage/HistoryManager.h"
#include "core/Snippet.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    qRegisterMetaType<Snippet>();
    
    app.setQuitOnLastWindowClosed(false);

    app.setOrganizationName("YourCompany");
    app.setApplicationName("ClipSyncPro");

    // Create all the application components
    HistoryManager historyManager;
    ClipboardManager clipboardManager(&historyManager);
    MainWindow window(&clipboardManager);
    SystemTray tray(&window);
    tray.show();

    // Set up and connect the global hotkey
    GlobalHotkey hotkey;
    app.installNativeEventFilter(&hotkey);
    QObject::connect(&hotkey, &GlobalHotkey::activated, &window, &MainWindow::toggleVisibility);

    // The 'aboutToQuit' connection has been removed as it is no longer needed.

    // Initialize the core logic
    clipboardManager.initialize();

    // Show the main window on startup
    window.show();

    // Start the Qt event loop
    return app.exec();
}