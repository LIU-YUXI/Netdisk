#include "netdisk.h"

#include <QApplication>
#include"communication.h"
Communication com("10.60.102.250",20600);
netdisk_message msg;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    netdisk w;
    com.connection();
    w.show();
    return a.exec();
}
