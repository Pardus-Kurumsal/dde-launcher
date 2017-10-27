/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -a dbuslauncherservice -c DBusLauncherService -l DBusLauncherService com.deepin.dde.Launcher.xml
 *
 * qdbusxml2cpp is Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#include "dbuslauncherservice.h"

#include <QtCore/QMetaObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QX11Info>

/*
 * Implementation of adaptor class DBusLauncherService
 */

DBusLauncherService::DBusLauncherService(LauncherSys *parent)
    : QDBusAbstractAdaptor(parent)
{
    // constructor
    setAutoRelaySignals(true);
}

DBusLauncherService::~DBusLauncherService()
{
    // destructor
}

void DBusLauncherService::Exit()
{
    // handle method call com.deepin.dde.Launcher.Exit
    qApp->quit();
}

void DBusLauncherService::Hide()
{
    // handle method call com.deepin.dde.Launcher.Hide
    parent()->hideLauncher();
    emit Closed();
}

void DBusLauncherService::Show()
{
    // handle method call com.deepin.dde.Launcher.Show
    parent()->showLauncher();
    emit Shown();
}

void DBusLauncherService::ShowByMode(qlonglong in0)
{
    // handle method call com.deepin.dde.Launcher.ShowByMode
    qDebug() << in0;
}

#ifndef WITHOUT_UNINSTALL_APP
void DBusLauncherService::UninstallApp(const QString &appKey)
{
    parent()->uninstallApp(appKey);
}
#endif

void DBusLauncherService::Toggle()
{
    // handle method call com.deepin.dde.Launcher.Toggle
    if (parent()->visible())
    {
        parent()->hideLauncher();
        emit Closed();
    } else {
        parent()->showLauncher();
        emit Shown();
    }
}
