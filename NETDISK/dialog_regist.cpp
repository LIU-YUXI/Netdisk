#include "dialog_regist.h"
#include "ui_dialog_regist.h"
#include "communication.h"
#include "fileactions.h"
#include<QDebug>
extern Communication com;
extern netdisk_message msg;
extern string clientname;

Dialog_regist::Dialog_regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_regist)
{
    ui->setupUi(this);
}

Dialog_regist::~Dialog_regist()
{
    delete ui;
}


void Dialog_regist::on_finish_clicked()
{
    QString passwd1=ui->password1->toPlainText();
    QString passwd2=ui->password2->toPlainText();
    if(passwd1!=passwd2){
        ui->msg->setText("密码输入不一致");
        return;
    }
    netdisk_message msg;
    ui->msg->clear();
    com.send_usermessage(REGIST,ui->username->toPlainText().toStdString(),
                         ui->account->toPlainText().toStdString(),
                         passwd1.toStdString());

    com.recv_message(msg);
    print(msg);
    if(!msg.user_correct){
        ui->msg->setText("账号已经存在");
        return;
    }
    ui->msg->clear();
    if(msg.user_correct){
        ui->msg->setText("注册成功,3s后自动跳转");
    }

    mysleep(3);
    this->close();

}
