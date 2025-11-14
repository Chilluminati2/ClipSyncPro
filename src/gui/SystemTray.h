// src/gui/SystemTray.h
#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QObject>
#include <QSystemTrayIcon> 


class QMenu;
class QWidget;


class SystemTray : public QObject {
    Q_OBJECT

public:
    // We pass a pointer to the main window so the tray can show/hide it
    explicit SystemTray(QWidget* parent = nullptr);
    void show(); // Call this to make the icon appear

private slots:
    // This is called when the user clicks on the tray icon
    void onIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void createMenu();

    QSystemTrayIcon* m_trayIcon;
    QMenu* m_trayMenu;
    QWidget* m_parentWindow; // A pointer to our MainWindow
};

#endif // SYSTEMTRAY_H