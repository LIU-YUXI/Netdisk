#include "folder.h"
#include "ui_folder.h"

folder::folder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::folder)
{
    ui->setupUi(this);
}

folder::~folder()
{
    delete ui;
}
