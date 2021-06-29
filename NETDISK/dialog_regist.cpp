#include "dialog_regist.h"
#include "ui_dialog_regist.h"

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
