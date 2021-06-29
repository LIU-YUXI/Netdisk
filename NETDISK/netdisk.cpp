#include "netdisk.h"
#include "ui_netdisk.h"
#include "dialog_folder.h"
#include "dialog_regist.h"

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


void netdisk::on_pushButton_clicked()
{
    this->close();
    Dialog_folder df;
    df.show();
    df.exec();
    this->show();
}

void netdisk::on_pushButton_2_clicked()
{
    this->close();
    Dialog_regist dr;
    dr.show();
    dr.exec();
    this->show();
}
