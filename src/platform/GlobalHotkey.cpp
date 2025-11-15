// src/platform/GlobalHotkey.cpp
#include "GlobalHotkey.h"
#include <windows.h> // Include the Windows header
#include <QDebug>

// A unique ID for our hotkey
#define MY_HOTKEY_ID 1

GlobalHotkey::GlobalHotkey(QObject *parent) : QObject(parent) {
    if (!registerHotkey()) {
        qWarning("Failed to register global hotkey. It might be in use by another application.");
    }
}

GlobalHotkey::~GlobalHotkey() {
    unregisterHotkey();
}

bool GlobalHotkey::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) {
    // This function acts as a message filter for the entire application
    if (eventType == "windows_generic_MSG") {
        MSG* msg = static_cast<MSG*>(message);
        
        // We are only interested in WM_HOTKEY messages
        if (msg->message == WM_HOTKEY) {
            // Check if it's our hotkey
            if (msg->wParam == MY_HOTKEY_ID) {
                emit activated(); // Emit our signal
                return true; // We handled this message
            }
        }
    }
    return false; // Let other handlers process this message
}

bool GlobalHotkey::registerHotkey() {
    // Register Ctrl+Shift+V
    // MOD_CONTROL is for Ctrl, MOD_SHIFT is for Shift, 0x56 is the virtual key code for 'V'
    return RegisterHotKey(NULL, MY_HOTKEY_ID, MOD_CONTROL | MOD_SHIFT, 0x56);
}

void GlobalHotkey::unregisterHotkey() {
    UnregisterHotKey(NULL, MY_HOTKEY_ID);
}