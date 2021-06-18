#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QMainWindow>

namespace Ui {
class download;
}

class download : public QMainWindow
{
    Q_OBJECT

public:
    explicit download(QWidget *parent = nullptr);
    ~download();

private:
    Ui::download *ui;
};

#endif // DOWNLOAD_H
