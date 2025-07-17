#pragma once
#include <QString>
#include <QSqlDatabase>
class DatabaseManager
{
public:
    static DatabaseManager& instance();
    bool init(const QString& dirPath = "db/PM_Register.db");

    QSqlDatabase database();

    bool createLogTable();


private:
    DatabaseManager() = default;
    ~DatabaseManager();

    //禁止拷贝和赋值
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase m_db;

};


