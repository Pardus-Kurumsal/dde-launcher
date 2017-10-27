/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/
#ifndef MENUWORKER_H
#define MENUWORKER_H

#include <QVariant>
#include <QProcess>
#include <QX11Info>
#include <QDBusObjectPath>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDBusPendingReply>
#include <QtCore>
#include <QModelIndex>

#include "dbusmenu.h"
#include "dbusmenumanager.h"
#include "dbusdock.h"
#include "dbuslauncher.h"
#include "dbustartmanager.h"
#include "model/appsmanager.h"
#include "model/appslistmodel.h"


#define MenuManager_service "com.deepin.menu"
#define MenuManager_path "/com/deepin/menu"


class MenuWorker : public QObject
{
    Q_OBJECT

public:

    explicit MenuWorker(QObject *parent = 0);
    ~MenuWorker();

    void initConnect();
    bool isMenuShown() const {return m_menuIsShown;}
    bool isItemOnDock(QString appKey);
    bool isItemOnDesktop(QString appKey);
    bool isItemStartup(QString appKey);

    QJsonObject createMenuItem(int itemId, QString itemText, bool isActive = true);
    QJsonObject createSeperator();

    QString createMenuContent();
    QString registerMenu();
    QString JsonToQString(QPoint pos, QString menucontent);

signals:
    void menuAccepted();
    void quitLauncher();
    void unInstallApp(const QModelIndex &index);

public slots:
    void showMenuByAppItem(const QModelIndex &index, QPoint pos);
    void menuItemInvoked(QString itemId, bool flag);

    void showMenu(QString menuDBusObjectPath, QString menuContent);
    void hideMenu(const QString& menuDBusObjectPath);
    void hideMenuByAppKey(const QString& appKey);

    void handleOpen();
    void handleToDesktop();
    void handleToDock();
    void handleToStartup();

    void handleMenuClosed();
    void setCurrentModelIndex(const QModelIndex &index);
    const QModelIndex getCurrentModelIndex();
private:
    DBusMenuManager* m_menuManagerInterface;
    DBusMenu* m_menuInterface;
    DBusDock* m_dockAppManagerInterface;
    DBusLauncher* m_launcherInterface;
    DBusStartManager* m_startManagerInterface;

    AppsManager *m_appManager;

    QModelIndex m_currentModelIndex = QModelIndex();
    QString m_appKey;
    QString m_appDesktop;
    QString m_currentMenuObjectPath;
    QMap<QString, QString> m_menuObjectPaths;
    bool m_isItemOnDesktop;
    bool m_isItemOnDock;
    bool m_isItemStartup;
    bool m_isRemovable;

    bool m_menuIsShown = false;
};

#endif // MENUWORKER_H
