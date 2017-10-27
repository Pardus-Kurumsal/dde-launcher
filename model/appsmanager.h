#ifndef APPSMANAGER_H
#define APPSMANAGER_H

#include "appslistmodel.h"
#include "dbuslauncher.h"
#include "dbusfileinfo.h"
#include "dbustartmanager.h"
#include "dbusdock.h"
#include "dbusdisplay.h"
#include "global_util/calculate_util.h"
#include "global_util/themeappicon.h"

#include <QMap>
#include <QSettings>
#include <QPixmap>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDBusArgument>
#include <QList>

#define DOCK_POS_RIGHT  1

class CalculateUtil;
class AppsManager : public QObject
{
    Q_OBJECT

public:
    static AppsManager *instance();

    void stashItem(const QModelIndex &index);
    void stashItem(const QString &appKey);
    void abandonStashedItem(const QString &appKey);
    void restoreItem(const QString &appKey, const int pos = -1);
    int dockPosition() const;
    int dockWidth() const;

signals:
    void dataChanged(const AppsListModel::AppCategory category) const;
    void layoutChanged(const AppsListModel::AppCategory category) const;
    void requestTips(const QString &tips) const;
    void requestHideTips() const;
    void categoryListChanged() const;
    void dockGeometryChanged() const;

public slots:
    void saveUserSortedList();
    void searchApp(const QString &keywords);
    void launchApp(const QModelIndex &index);
    void uninstallApp(const QString &appKey);
    const ItemInfoList appsInfoList(const AppsListModel::AppCategory &category) const;

    bool appIsNewInstall(const QString &key);
    bool appIsAutoStart(const QString &desktop);
    bool appIsOnDock(const QString &desktop);
    bool appIsOnDesktop(const QString &desktop);
    const QPixmap appIcon(const QString &iconKey, const int size);
    int appNums(const AppsListModel::AppCategory &category) const;

    // TODO: optimize
    void handleItemChanged(const QString &operation, const ItemInfo &appInfo, qlonglong categoryNumber);

private:
    explicit AppsManager(QObject *parent = 0);

    const QPixmap loadSvg(const QString &fileName, const int size);
    const QPixmap loadIconFile(const QString &fileName, const int size);
    void appendSearchResult(const QString &appKey);
    void sortCategory(const AppsListModel::AppCategory category);
    void sortByPresetOrder(ItemInfoList &processList);
    void refreshCategoryInfoList();
    void generateCategoryMap();
    void refreshAppAutoStartCache();

private slots:
    void searchDone(const QStringList &resultList);
    void markLaunched(QString appKey);

private:
    DBusLauncher *m_launcherInter;
    DBusStartManager *m_startManagerInter;
    DBusDock *m_dockInter;

    QPixmap m_defaultIconPixmap;
    QString m_searchText;
    QStringList m_newInstalledAppsList;
    ItemInfoList m_allAppInfoList;
    ItemInfoList m_userSortedList;
    ItemInfoList m_appSearchResultList;
    ItemInfoList m_stashList;
    QMap<AppsListModel::AppCategory, ItemInfoList> m_appInfos;

    ItemInfo m_unInstallItem = ItemInfo();
    ItemInfo m_beDragedItem = ItemInfo();

    ThemeAppIcon* m_themeAppIcon;
    CalculateUtil *m_calUtil;
    QTimer *m_searchTimer;

    static QPointer<AppsManager> INSTANCE;
    static QGSettings APP_PRESET_SORTED_LIST;
    static QSettings APP_AUTOSTART_CACHE;
    static QSettings APP_USER_SORTED_LIST;
};

#endif // APPSMANAGER_H
