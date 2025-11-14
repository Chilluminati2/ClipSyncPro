// src/main.cpp
#include <QApplication>
#include "gui/MainWindow.h"
#include "core/ClipboardManager.h"
#include "storage/HistoryManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set company and app name for settings storage
    app.setOrganizationName("YourCompany");
    app.setApplicationName("ClipSyncPro");

    // 1. Create the components
    HistoryManager historyManager;
    ClipboardManager clipboardManager(&historyManager);
    MainWindow window(&clipboardManager);

    // 2. Initialize the core logic
    clipboardManager.initialize();

    // 3. Show the user interface
    window.show();

    return app.exec();
}