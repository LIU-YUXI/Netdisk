#include "netdisk.h"
#include "ui_netdisk.h"
#include "dialog_folder.h"
#include "dialog_regist.h"
#include "communication.h"
#include "fileactions.h"

extern Communication com;
extern netdisk_message msg;
netdisk::netdisk(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::netdisk)
{
    ui->setupUi(this);
}

netdisk::~netdisk()
{
    delete ui;
}


void netdisk::on_login_clicked()
{

    com.send_usermessage(LOGIN,ui->username->toPlainText().toStdString(),
                                   ui->username->toPlainText().toStdString(),
                                   ui->password->toPlainText().toStdString());
    netdisk_message msg;
    com.recv_message(msg);
    if(!msg.user_correct){
        ui->show->setText("密码或账号错误");
        return;
    }
    else
        ui->show->clear();
    this->close();
    makesureConfigexist();
    createFoldersbyFile("C:\\mycloud\\Liu\\usrconfig.conf","C:\\mycloud\\Liu");
    startMonitor("C:\\mycloud\\Liu\\usrconfig.conf");
    Dialog_folder df;
    df.show();
    df.exec();
    this->show();
}

void netdisk::on_regist_clicked()
{
    this->close();
    Dialog_regist dr;
    dr.show();
    dr.exec();
    this->show();
}
