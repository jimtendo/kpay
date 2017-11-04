#ifndef KPAYMAINWINDOW_H
#define KPAYMAINWINDOW_H

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>

class EngineInterface;
class EngineProvider;

class KPayMainWindow : public QApplication
{
    Q_OBJECT

public:
    explicit KPayMainWindow(int &argc, char **argv);
    ~KPayMainWindow();
    
signals:
    
private:
    QSystemTrayIcon *trayIcon;
    QQmlApplicationEngine *m_qmlEngine;
    EngineProvider *m_engineProvider;
};

#endif // KPAYMAINWINDOW_H
