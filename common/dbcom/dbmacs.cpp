/*
 *
 *  Created on: 2021年1月1日
 *      Author: Lzy
 */
#include "dbmacs.h"

DbMacs::DbMacs()
{
    createTable();
    tableTile = tr("MAC记录");
    //hiddens <<  9;
    headList << tr("客户名称") << tr("软件版本") << tr("SN码") << tr("MAC地址");
}

void DbMacs::createTable()
{
    QString cmd =
            "create table if not exists %1("
            "id             INTEGER primary key autoincrement not null,"
            "date           VCHAR,"
            "time           VCHAR,"
            "user           VCHAR,"
            "fw             VCHAR,"
            "sn             VCHAR,"
            "mac            VCHAR not null);";
    QSqlQuery query(mDb);
    if(!query.exec(cmd.arg(tableName()))) {
        throwError(query.lastError());
    }
}

DbMacs *DbMacs::bulid()
{
    static DbMacs* sington = nullptr;
    if(sington == nullptr)
        sington = new DbMacs();
    return sington;
}

bool DbMacs::insertItem(sMacItem &item)
{
    QString cmd = "insert into %1 (date,time,user,fw,sn,mac) "
                  "values(:date,:time,:user,:fw,:sn,:mac)";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret) emit itemChanged(item.id,Insert);
    return ret;
}

int DbMacs::contains(const QString &mac)
{
    QString condition = QString("where mac=\'%1\'").arg(mac);

    return count("mac", condition);
}

bool DbMacs::updateItem(const sMacItem &item)
{
    QString cmd = "update %1 set "
                  "user         = :user,"
                  "fw           = :fw,"
                  "sn           = :sn,"
                  "mac          = :mac"
                  " where id    = :id";
    bool ret = modifyItem(item,cmd.arg(tableName()));
    if(ret) emit itemChanged(item.id,Update);

    return ret;
}

bool DbMacs::modifyItem(const sMacItem &item, const QString &cmd)
{
    QSqlQuery query(mDb);
    query.prepare(cmd);
    if(cmd.contains("id")) {
        query.bindValue(":id",item.id);
    }

    query.bindValue(":date",item.date);
    query.bindValue(":time",item.time);
    query.bindValue(":user",item.user);
    query.bindValue(":fw",item.fw);
    query.bindValue(":sn",item.sn);
    query.bindValue(":mac",item.mac);
    bool ret = query.exec();
    if(!ret)  throwError(query.lastError());
    return ret;
}

void DbMacs::selectItem(QSqlQuery &query,sMacItem &item)
{
    item.id = query.value("id").toInt();
    item.date = query.value("date").toString();
    item.time = query.value("time").toString();
    item.user = query.value("user").toString();
    item.fw = query.value("fw").toString();
    item.sn = query.value("sn").toString();
    item.mac = query.value("mac").toString();
}


sMacItem DbMacs::selItemByMac(const QString& mac)
{
    QVector<sMacItem> items = selectItems(QString("where mac = \'%1\'").arg(mac));
    return items.first();
}


void DbMacs::removeMac(const QString& mac)
{
    remove(QString("mac = \'%1\'").arg(mac));
}
