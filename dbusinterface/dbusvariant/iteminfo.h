#ifndef ITEMINFO_H
#define ITEMINFO_H

#include "model/appslistmodel.h"

#include <QtDBus>

class ItemInfo
{
public:
    ItemInfo();
    ~ItemInfo();

    static void registerMetaType();

    AppsListModel::AppCategory category() const;

    bool operator==(const ItemInfo &other) const;
    friend QDebug operator<<(QDebug argument, const ItemInfo &info);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const ItemInfo &info);
    friend QDataStream &operator<<(QDataStream &argument, const ItemInfo &info);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, ItemInfo &info);
    friend const QDataStream &operator>>(QDataStream &argument, ItemInfo &info);


public:
    QString m_desktop;
    QString m_name;
    QString m_key;
    QString m_iconKey;
    qlonglong m_categoryId;
    qlonglong m_installedTime;
};

typedef QList<ItemInfo> ItemInfoList;

Q_DECLARE_METATYPE(ItemInfo)
Q_DECLARE_METATYPE(ItemInfoList)

#endif // ITEMINFO_H
