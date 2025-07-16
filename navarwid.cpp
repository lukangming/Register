#include "navarwid.h"
#include "ui_navarwid.h"
#include "backcolourcom.h"
#include "servicesettingdialog.h"
#include <QDebug>
#include <QMessageBox>

navarwid::navarwid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::navarwid)
{
    ui->setupUi(this);
    set_background_icon(this,":/image/title_back.jpg");

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


void navarwid::on_SerSet_clicked()
{
    ServiceSettingDialog dlg(this);
    dlg.setWindowTitle("服务设置");
    // 1. 创建 QSettings 对象（和主程序用同一个路径）
    QSettings settings(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);

    // 2. 加载设置
    dlg.loadSettings(settings);

    if (dlg.exec() == QDialog::Accepted) {
        if (m_keygenWidget) {
            m_keygenWidget->setAesConfig(dlg.getAesConfig());
            m_keygenWidget->setSaveDir(dlg.getSavePath());
            //QMessageBox::information(this, "提示", "加密配置已更新！");
            dlg.saveSettings(settings);
        } else {
            QMessageBox::warning(this, "错误", "Keygen 未初始化，无法更新配置！");
        }
    }
}

void navarwid::setKeygenWidget(Keygen *keygen)
{
    m_keygenWidget = keygen;
}
