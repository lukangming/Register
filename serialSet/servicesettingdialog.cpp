#include "servicesettingdialog.h"
#include "ui_servicesettingdialog.h"
#include "backcolour/backcolourcom.h"
#include <QMessageBox>
#include <QFileDialog>
ServiceSettingDialog::ServiceSettingDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServiceSettingDialog)
{
    ui->setupUi(this);

    set_background_icon(this,":/image/box_back.jpg");
    ui->saveDir->setReadOnly(true);
    initDialog();

}

void ServiceSettingDialog::initDialog()
{
    ui->comboBoxLevel->addItem("AES 128", QAESEncryption::AES_128);
    ui->comboBoxLevel->addItem("AES 192", QAESEncryption::AES_192);
    ui->comboBoxLevel->addItem("AES 256", QAESEncryption::AES_256);
    ui->comboBoxLevel->setCurrentIndex(2); // 默认256

    ui->comboBoxMode->addItem("ECB", QAESEncryption::ECB);
    ui->comboBoxMode->addItem("CBC", QAESEncryption::CBC);
    ui->comboBoxMode->addItem("CFB", QAESEncryption::CFB);
    ui->comboBoxMode->addItem("OFB", QAESEncryption::OFB);
    ui->comboBoxMode->setCurrentIndex(1); // 默认CBC

    ui->comboBoxPadding->addItem("ZERO", QAESEncryption::ZERO);
    ui->comboBoxPadding->addItem("PKCS7", QAESEncryption::PKCS7);
    ui->comboBoxPadding->addItem("ISO", QAESEncryption::ISO);
    ui->comboBoxPadding->setCurrentIndex(2); // 默认PKCS7

    // 初始化密钥和IV，默认值用构造函数的默认
    m_config = sAesItf();
    ui->lineEditKey->setText(QString(m_config.key.toHex()));
    ui->lineEditIv->setText(QString(m_config.iv.toHex()));
    //ui->saveDir->setText()
}

ServiceSettingDialog::~ServiceSettingDialog()
{
    delete ui;
}

void ServiceSettingDialog::on_buttonBox_accepted()
{
    // 先准备临时变量保存用户输入
    auto level = static_cast<QAESEncryption::Aes>(ui->comboBoxLevel->currentData().toInt());
    auto mode = static_cast<QAESEncryption::Mode>(ui->comboBoxMode->currentData().toInt());
    auto padding = static_cast<QAESEncryption::Padding>(ui->comboBoxPadding->currentData().toInt());
    QByteArray key = QByteArray::fromHex(ui->lineEditKey->text().toUtf8());
    QByteArray iv = QByteArray::fromHex(ui->lineEditIv->text().toUtf8());

    // 先校验
    bool validKeyLength = false;
    switch (level) {
    case QAESEncryption::AES_128: validKeyLength = (key.size() == 16); break;
    case QAESEncryption::AES_192: validKeyLength = (key.size() == 24); break;
    case QAESEncryption::AES_256: validKeyLength = (key.size() == 32); break;
    default: validKeyLength = false;
    }
    if (!validKeyLength) {
        QMessageBox::warning(this, "错误", "密钥长度不正确，请输入对应长度的16/24/32字节密钥（十六进制字符串）");
        return; // 直接返回，不修改 m_config，不关闭对话框
    }

    if (mode != QAESEncryption::ECB && iv.size() != 16) {
        QMessageBox::warning(this, "错误", "IV长度必须为16字节（十六进制字符串），ECB模式下可为空");
        return;
    }

    // 校验通过，赋值
    m_config.level = level;
    m_config.mode = mode;
    m_config.padding = padding;
    m_config.key = key;
    m_config.iv = iv;

    QMessageBox::information(this, "提示", "配置已保存");
    accept();  // 关闭对话框，确认保存
}

void ServiceSettingDialog::on_changeDirBtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "选择保存目录", QCoreApplication::applicationDirPath());
    if (!dir.isEmpty()) {
        m_savePath = dir; // m_saveDir 成员变量，保存目录路径
        ui->saveDir->setText(dir); // 显示目录的 QLineEdit
    }
}

sAesItf ServiceSettingDialog::getAesConfig() const
{
    return m_config;  // 假设你内部用 m_config 存储配置
}

QString ServiceSettingDialog::getSavePath() const
{
    return m_savePath;
}

void ServiceSettingDialog::loadSettings(QSettings &settings)
{
    m_savePath = settings.value("saveDir", "").toString();
    if (ui->saveDir) {
        ui->saveDir->setText(m_savePath);
    }

    settings.beginGroup("sAesItf");
    m_config.level = static_cast<QAESEncryption::Aes>(settings.value("level", static_cast<int>(m_config.level)).toInt());
    m_config.mode = static_cast<QAESEncryption::Mode>(settings.value("mode", static_cast<int>(m_config.mode)).toInt());
    m_config.padding = static_cast<QAESEncryption::Padding>(settings.value("padding", static_cast<int>(m_config.padding)).toInt());
    m_config.key = QByteArray::fromHex(settings.value("key", QString(m_config.key.toHex())).toString().toUtf8());
    m_config.iv = QByteArray::fromHex(settings.value("iv", QString(m_config.iv.toHex())).toString().toUtf8());
    settings.endGroup();

    // 同步到界面
    ui->comboBoxLevel->setCurrentIndex(ui->comboBoxLevel->findData(m_config.level));
    ui->comboBoxMode->setCurrentIndex(ui->comboBoxMode->findData(m_config.mode));
    ui->comboBoxPadding->setCurrentIndex(ui->comboBoxPadding->findData(m_config.padding));
    ui->lineEditKey->setText(QString(m_config.key.toHex()));
    ui->lineEditIv->setText(QString(m_config.iv.toHex()));
}

void ServiceSettingDialog::saveSettings(QSettings &settings)
{
    settings.setValue("saveDir", m_savePath);

    settings.beginGroup("sAesItf");
    settings.setValue("level", static_cast<int>(m_config.level));
    settings.setValue("mode", static_cast<int>(m_config.mode));
    settings.setValue("padding", static_cast<int>(m_config.padding));
    settings.setValue("key", QString(m_config.key.toHex()));
    settings.setValue("iv", QString(m_config.iv.toHex()));
    settings.endGroup();
}
