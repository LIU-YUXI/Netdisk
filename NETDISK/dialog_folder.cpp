#include "dialog_folder.h"
#include "ui_dialog_folder.h"
#include"fileactions.h"
#include <QDebug>
extern string clientname;
extern string downloading_file;
extern string uploading_file;

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
    std::string FileTree=openFile("C:\\mycloud\\"+clientname+"\\usrconfig.conf",
                                              file1.length()+clientname.length()+1,SHOWTREE);
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
        bondDir("C:\\mycloud\\"+clientname+"\\usrconfig.conf",
                ui->cloudpath->toPlainText().toStdString(),ui->localpath->toPlainText().toStdString());

    }
    if(status==UNBONDPATH){
        unbondDir("C:\\mycloud\\"+clientname+"\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString());
    }
    if(status==DELETEPATH){
        deleteDir("C:\\mycloud\\"+clientname+"\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString(), clientname);
    }
    if(status==ADDPATH){
        addDir("C:\\mycloud\\"+clientname+"\\usrconfig.conf", ui->cloudpath->toPlainText().toStdString(),clientname);
    }

    ui->cloudpath->setDisabled(true);
    ui->localpath->setDisabled(true);

    ui->confirm->setDisabled(true);
}



void Dialog_folder::on_filearray_clicked()
{
    if(downloading_file!=""){
        ui->textBrowser->clear();
        QString show="当前正在下载：";
        ui->textBrowser->setText(show+downloading_file.c_str());
    }
    else if(uploading_file!=""){
        ui->textBrowser->clear();
        QString show="当前正在上传：";
        ui->textBrowser->setText(show+uploading_file.c_str());
    }
}
