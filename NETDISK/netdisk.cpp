#include "netdisk.h"
#include "ui_netdisk.h"
#include "dialog_folder.h"
#include "dialog_regist.h"
#include "communication.h"
#include "fileactions.h"

extern Communication com;
extern netdisk_message msg;
extern string clientname;
extern string uploading_file;
extern string downloading_file;
extern string logfile;
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
    boolean temp=msg.user_correct;
    qDebug()<<temp<<endl;
    if(temp==false){
        ui->show->setText("密码或账号错误");
        qDebug()<<msg.user_correct<<"wrong"<<endl;
        return;
    }
    else
        ui->show->clear();

    logfile=file1+clientname+"\\"+"run.log";
    clientname=ui->username->toPlainText().toStdString();
    com.recv_message(msg);
    qDebug()<<"debug1"<<endl;
    if(msg.op==SENDCONFIG){
        qDebug()<<"receive"<<endl;
        ofstream out;
        downloading_file="usrconfig.conf";
        out.open("C:\\mycloud\\"+clientname+"\\usrconfig.conf",ios::out);
        while(1){
            //com.recv_message(msg);
            qDebug()<<msg.content.c_str()<<endl;
            qDebug()<<"msghere"<<endl;
            out<<msg.content;
            if(msg.is_tail==true){
                com.send_message(FINISH,"",false,"","","");
                break;
            }
        }
        out.close();
        downloading_file.clear();
    }
    else{
        qDebug()<<"send"<<endl;
        Sleep(100000);
        string filename="C:\\mycloud\\"+clientname+"\\usrconfig.conf";
        string md5code=makesureConfigexist();
        string file;
        ifstream fin(filename.c_str(),ios::binary);//
        int count=0;
        char temp_ch;
        uploading_file="usrconfig.conf";
        while (1)
        {
            if(!fin.get(temp_ch)){
                com.send_message(SENDCONFIG,filename,true,"",md5code,file,-1,true);
                qDebug()<<file.c_str()<<endl;

                file.clear();
                com.recv_message(msg);
                if(msg.op==FINISH){

                    break;
                }
                else{
                    qDebug()<<"error"<<endl;
                    Sleep(1000);
                    qDebug()<<"huozhe"<<endl;
                    Sleep(1000);
                    qDebug()<<"haihuozhe"<<endl;
                    Sleep(1231231324);
                    break;
                }
            }
            count++;
            file += temp_ch;
            if(count==SENDFILESIZE){
                count=0;
                com.send_message(SENDCONFIG,filename,true,"",md5code,file);
                file.clear();
                com.recv_message(msg);
                if(msg.op==FINISH)
                    continue;
            }
        }
        uploading_file.clear();

    }
    this->close();

    RemoveDirectoryA(("C:\\mycloud\\"+clientname).c_str());
    createFoldersbyFile("C:\\mycloud\\"+clientname+"\\usrconfig.conf","C:\\mycloud\\"+clientname);
    openFile(("C:\\mycloud\\"+clientname+"\\usrconfig.conf").c_str(),
             ("C:\\mycloud\\"+clientname+"\\").length(),CHECKMD5);
    com.send_message(FINISH_INITIAL,"",false,"","","");
    receiveFiles();
    startMonitor("C:\\mycloud\\"+clientname+"\\usrconfig.conf");
    
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
