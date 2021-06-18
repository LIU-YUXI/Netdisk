#ifndef FOLDER_H
#define FOLDER_H

#include <QMainWindow>

namespace Ui {
class folder;
}

class folder : public QMainWindow
{
    Q_OBJECT

public:
    explicit folder(QWidget *parent = nullptr);
    ~folder();

private:
    Ui::folder *ui;
};

#endif // FOLDER_H
