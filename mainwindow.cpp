#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbcom/databasemanager.h"
#include <QSettings>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mkeygen(new Keygen(this))

{
    ui->setupUi(this);

   // initDataBase(); // 添加数据库并建表

    initWid();
    loadAllSettings(); //读写配置文件
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDataBase()
{
    QString appDir = QCoreApplication::applicationDirPath();
    QString dbDir = appDir + "/db";
    QDir dir(dbDir);
    if(!dir.exists()){
        dir.mkpath(".");
    }

    QString dbFilePath = dbDir + "/PM_Register.db";

    if(!DatabaseManager::instance().init(dbFilePath)){
       // qDebug() << "数据库初始化失败";
    } else{
       // qDebug() << "数据库初始化成功";
    }
}

void MainWindow::initWid()
{
    mNavar = new navarwid(ui->barWid);
    ui->stackedWidget->addWidget(mkeygen);
    mNavar->setKeygenWidget(mkeygen);
}

void MainWindow::navBarSlot(int id)
{
    qDebug()<<"current page:  "<<id;
    ui->stackedWidget->setCurrentIndex(id);
}

void MainWindow::saveAllSettings() {
    QString configPath = QCoreApplication::applicationDirPath() + "/config.ini";
//    qDebug() << "Saving to:" << configPath;

    QSettings settings(configPath, QSettings::IniFormat); // 这里使用完整路径

    settings.sync(); // 同步写磁盘
}

void MainWindow::loadAllSettings() {
    QString configPath = QCoreApplication::applicationDirPath() + "/config.ini";

    QSettings settings(configPath, QSettings::IniFormat); // 这里使用完整路径

    mkeygen->loadSettings(settings);;

}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveAllSettings();
    QMainWindow::closeEvent(event);
}
