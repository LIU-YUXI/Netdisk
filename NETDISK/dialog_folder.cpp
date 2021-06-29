#include "dialog_folder.h"
#include "ui_dialog_folder.h"

Dialog_folder::Dialog_folder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_folder)
{
    ui->setupUi(this);
}

Dialog_folder::~Dialog_folder()
{
    delete ui;
}
