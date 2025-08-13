#include "navarwid.h"
#include "ui_navarwid.h"
#include "backcolourcom.h"
//#include "servicesettingdialog.h"
#include <QDebug>
#include <QMessageBox>

navarwid::navarwid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::navarwid)
{
    ui->setupUi(this);
    QGridLayout *gridLayout = new QGridLayout(parent);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(this);
    set_background_icon(this,":/image/title_back.jpg");
    mUserLand = new UsrLandDlg(this);
    QTimer::singleShot(5,this,SLOT(on_loginBtn_clicked()));
    connect(mUserLand,SIGNAL(sendUserNameSig(QString)),this,SLOT(recvUserNameSlot(QString)));
}

navarwid::~navarwid()
{
    delete ui;
}

void navarwid::on_MainWid_clicked()
{
    //qDebug()<<"1";
    emit navBarSig(0);
}

void navarwid::on_setBtn_clicked()
{
    emit navBarSig(1);
}


void navarwid::on_loginBtn_clicked()
{
    bool lang = LandingUser::get()->land;
    if(lang) {
        int ret = mUserLand->selectWork();
        if(ret == 1) { // 用户切换
            mUserLand->exec();
        }  else if(ret == 2) { // 用户退出
            mUserLand->quitWidget();
        }
    } else {
        mUserLand->exec();
    }
}

void navarwid::recvUserNameSlot(QString str)
{
    ui->userLab->setText(str);
}
