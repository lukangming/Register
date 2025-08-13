#include "serialstatuswid.h"
#include "ui_serialstatuswid.h"
#include "serialportdialog.h"

#include <QDebug>


SerialStatusWid::SerialStatusWid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SerialStatusWid)
    , serial (new QSerialPort(this))
{
    ui->setupUi(this);
}

SerialStatusWid::~SerialStatusWid()
{
    delete ui;
}




