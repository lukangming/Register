/*
 * newusrdlg.cpp
 *  用户增加界面
 *  新用户信息增加
 *
 *  Created on: 2016年10月11日
 *      Author: Lzy
 */
#include "newusrdlg.h"
#include "ui_newusrdlg.h"

NewUsrDlg::NewUsrDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewUsrDlg)
{
    ui->setupUi(this);
    groupBox_background_icon(this);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->TelephonelineEdit);
    ui->TelephonelineEdit->setValidator( validator );
}

NewUsrDlg::~NewUsrDlg()
{
    delete ui;
}

/**
 * @brief 修改标题
 * @param str
 */
void NewUsrDlg::editTitle(const QString &str)
{
    ui->NamelineEdit->setEnabled(false);
    ui->Titlelabel->setText(str);
    this->setWindowTitle(str);

    checkUsr();
}

/**
 * @brief 编辑时，如果只有一个账户，这个账户只能是管理员
 */
void NewUsrDlg::checkUsr(void)
{
    DbUser* db = DbUser::build();
    int ret = db->counts();
    if(ret <= 1) {
        ui->authcomboBox->setCurrentIndex(1);
        ui->authcomboBox->setDisabled(true);
    }
}


/**
 * @brief 用户信息加载
 * @param usr
 */
void NewUsrDlg::loadUsrInfo(sUserItem &user)
{
    ui->NamelineEdit->setText(user.name);
    ui->PwdlineEdit->setText(user.pwd);
    ui->pwd2lineEdit->setText(user.pwd);
    ui->authcomboBox->setCurrentIndex(user.jur);
    ui->TelephonelineEdit->setText(user.telephone);
    ui->EmaillineEdit->setText(user.email);
    ui->RemarkstextEdit->setText(user.remarks);
}


/**
 * @brief 输入信息检查
 * @return
 */
bool NewUsrDlg::inputCheck(void)
{
    QString str;

    str = ui->NamelineEdit->text();
    if(str.isEmpty())
    {
        MsgBox::critical(this, tr("账号不能为空"));
        return false;
    }

    str = ui->PwdlineEdit->text();
    if(str.isEmpty())
    {
        MsgBox::critical(this,  tr("密码不能为空"));
        return false;
    }

    if(str != ui->pwd2lineEdit->text())
    {
        MsgBox::critical(this,  tr("密码两次输入不一致"));
        return false;
    }

//    str = ui->EmaillineEdit->text();
//    if(str.isEmpty())
//    {
//        MsgBox::critical(this,  tr("请输入Email地址"));
//        return false;
//    }
//    if(!str.contains("@"))
//    {
//        MsgBox::critical(this,  tr("请输入合法Email地址"));
//        return false;
//    }

    str = ui->TelephonelineEdit->text();
    if(str.isEmpty())
    {
        MsgBox::critical(this, tr("请输入工号"));
        return false;
    }

   return true;
}

bool NewUsrDlg::saveUsrInfo(sUserItem &user)
{
    DbUser* db = DbUser::build();
    int rtn = db->contains(user.name);
    if(rtn > 0) return false;

    return db->insertItem(user);
}

void NewUsrDlg::on_saveBtn_clicked()
{
    if(inputCheck())
    {
        sUserItem user;
        user.name = ui->NamelineEdit->text();
        user.pwd = ui->PwdlineEdit->text();
        user.jur = ui->authcomboBox->currentIndex();
        user.jurisdiction = ui->authcomboBox->currentText();
        user.telephone = ui->TelephonelineEdit->text();
        user.email = ui->EmaillineEdit->text();
        user.remarks = ui->RemarkstextEdit->toPlainText();

        if(saveUsrInfo(user))
            accept();
        else
            MsgBox::critical(this,  tr("账号已存在"));
    }
}
