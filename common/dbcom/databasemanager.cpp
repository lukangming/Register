#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::~DatabaseManager()
{
    if(m_db.isOpen()){
        m_db.close();
    }
}

bool DatabaseManager::init(const QString& dbPath)
{
    if (QSqlDatabase::contains("AppConnection")) {
        m_db = QSqlDatabase::database("AppConnection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE", "AppConnection");
        m_db.setDatabaseName(dbPath);
    }

    if(!m_db.open()){
        //qDebug() << " Failed to open DB :"<< m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);


    // qDebug()<<1;
    // if (!query.exec("PRAGMA journal_mode=WAL;"))
    //     qDebug() << "⚠️ 设置 WAL 模式失败:" << query.lastError().text();
    // else
    //     qDebug() << "✅ WAL 模式已启用";

    // if (!query.exec("PRAGMA synchronous=NORMAL;"))
    //     qDebug() << "⚠️ 设置同步模式失败:" << query.lastError().text();
    // else
    //     qDebug() << "✅ 同步模式已设置为 NORMAL";

    // m_db.transaction();

    // if (!query.exec("PRAGMA cache_size=-8192;"))
    //     qDebug() << "⚠️ 设置缓存大小失败:" << query.lastError().text();
    // else
    //     qDebug() << "✅ 缓存大小已设置为 8MB";

    // if (!query.exec("PRAGMA temp_store=MEMORY;"))
    //     qDebug() << "⚠️ 设置临时存储模式失败:" << query.lastError().text();
    // else
    //     qDebug() << "✅ 临时存储模式已设置为 MEMORY";

    m_db.commit();
    qDebug() << "✅ Database opened at:" << dbPath;
    return true;
}
