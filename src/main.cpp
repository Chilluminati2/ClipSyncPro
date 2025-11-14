// src/main.cpp
#include <QApplication>
#include <QObject> // Needed for QObject::connect

#include "gui/MainWindow.h"
#include "gui/SystemTray.h" // Include our new class
#include "core/ClipboardManager.h"
#include "storage/HistoryManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // IMPORTANT: This line prevents the app from quitting when you close the main window.
    // Instead, the window will just hide, and the app will keep running in the tray.
    app.setQuitOnLastWindowClosed(false);

    // Standard application metadata
    app.setOrganizationName("YourCompany");
    app.setApplicationName("ClipSyncPro");

    // --- 1. Create all the application components ---
    HistoryManager historyManager;
    ClipboardManager clipboardManager(&historyManager);
    MainWindow window(&clipboardManager);
    
    // Create the system tray icon, passing it a pointer to our main window
    // so it can show/hide it.
    SystemTray tray(&window);
    tray.show(); // Makes the icon visible in the system tray

    // --- 2. Connect the application's quit signal to the save function ---
    // This is the guaranteed, robust way to save data right before the app fully exits.
    // This signal is emitted when you click "Quit" from the tray menu.
    QObject::connect(&app, &QApplication::aboutToQuit, &clipboardManager, &ClipboardManager::saveOnExit);

    // --- 3. Initialize the core logic ---
    // This loads the history from disk and starts monitoring the clipboard.
    clipboardManager.initialize();

    // --- 4. Show the main window on startup ---
    window.show();

    // --- 5. Start the Qt event loop ---
    // This line runs the application, processes events (like clicks and copies),
    // and only returns when the app quits.
    return app.exec();
}