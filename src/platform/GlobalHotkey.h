// src/platform/GlobalHotkey.h
#ifndef GLOBALHOTKEY_H
#define GLOBALHOTKEY_H

#include <QObject>
#include <QAbstractNativeEventFilter>

class GlobalHotkey : public QObject, public QAbstractNativeEventFilter {
    Q_OBJECT

public:
    explicit GlobalHotkey(QObject *parent = nullptr);
    ~GlobalHotkey();

    // The nativeEventFilter is where we will listen for the hotkey message from Windows
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

signals:
    void activated(); // Emitted when the hotkey is pressed

private:
    bool registerHotkey();
    void unregisterHotkey();
};

#endif // GLOBALHOTKEY_H