#ifndef DIALOG_FOLDER_H
#define DIALOG_FOLDER_H

#include <QDialog>

namespace Ui {
class Dialog_folder;
}

class Dialog_folder : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_folder(QWidget *parent = nullptr);
    ~Dialog_folder();

private:
    Ui::Dialog_folder *ui;
};

#endif // DIALOG_FOLDER_H
