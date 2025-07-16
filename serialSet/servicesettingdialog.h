#ifndef SERVICESETTINGDIALOG_H
#define SERVICESETTINGDIALOG_H

#include <QDialog>
#include "SettingsHelper.h"
namespace Ui {
class ServiceSettingDialog;
}

class ServiceSettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServiceSettingDialog(QWidget *parent = nullptr);
    ~ServiceSettingDialog();

    sAesItf getAesConfig() const;  //
    QString getSavePath() const;

    void initDialog();

    void loadSettings(QSettings &settings);
    void saveSettings(QSettings &settings);
private slots:
    void on_buttonBox_accepted();
    void on_changeDirBtn_clicked();

private:
    Ui::ServiceSettingDialog *ui;

    sAesItf m_config;  //加密配置信息
    QString m_savePath; //文件保存路径
};

#endif // SERVICESETTINGDIALOG_H
