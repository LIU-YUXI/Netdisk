#include "dialog_folder.h"
#include "ui_dialog_folder.h"
#include"fileactions.h"
#include <QDebug>
Dialog_folder::Dialog_folder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_folder)
{
    ui->setupUi(this);
}
int status;
Dialog_folder::~Dialog_folder()
{
    delete ui;
}

void Dialog_folder::on_myfile_clicked()
{
    std::string FileTree=openFile(std::string("C:\\mycloud\\Liu\\usrconfig.conf"),file1.length()+strlen("Liu")+1);
    QString show=FileTree.c_str();
    ui->textBrowser->setText(show);
}

void Dialog_folder::on_link_clicked()
{
    ui->cloudpath->setDisabled(false);
    ui->cloudpath->setPlainText("cloudpath");
    ui->localpath->setDisabled(false);
    ui->localpath->setPlainText("localpath");

    ui->confirm->setDisabled(false);
    status=BONDPATH;
}

void Dialog_folder::on_unlink_clicked()
{
    ui->cloudpath->setDisabled(false);
    ui->cloudpath->setPlainText("cloudpath");
    ui->localpath->setDisabled(true);

    ui->confirm->setDisabled(false);
    status=UNBONDPATH;
}

void Dialog_folder::on_addpath_clicked()
{
    ui->cloudpath->setDisabled(false);
    ui->cloudpath->setPlainText("cloudpath");
    ui->localpath->setDisabled(true);

    ui->confirm->setDisabled(false);
    status=ADDPATH;
}

void Dialog_folder::on_deletepath_clicked()
{
    ui->cloudpath->setDisabled(false);
    ui->cloudpath->setPlainText("cloudpath");
    ui->localpath->setDisabled(true);

    ui->confirm->setDisabled(false);
    status=DELETEPATH;
}

void Dialog_folder::on_confirm_clicked()
{
    if(status==BONDPATH){
        bondDir("C:\\mycloud\\Liu\\usrconfig.conf",ui->cloudpath->toPlainText().toStdString(),ui->localpath->toPlainText().toStdString());

    }
    if(status==UNBONDPATH){
        unbondDir("C:\\mycloud\\Liu\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString());
    }
    if(status==DELETEPATH){
        deleteDir("C:\\mycloud\\Liu\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString(), "Liu");
    }
    if(status==ADDPATH){
        addDir("C:\\mycloud\\Liu\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString(),"Liu");
    }

    ui->cloudpath->setDisabled(true);
    ui->localpath->setDisabled(true);

    ui->confirm->setDisabled(true);
}


