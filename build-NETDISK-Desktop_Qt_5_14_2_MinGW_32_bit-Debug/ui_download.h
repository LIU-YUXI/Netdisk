/********************************************************************************
** Form generated from reading UI file 'download.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOAD_H
#define UI_DOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_download
{
public:
    QWidget *centralwidget;
    QPushButton *myfile;
    QPushButton *logout;
    QPushButton *pushButton_3;
    QLabel *label;
    QTableView *tableView;
    QTableView *tableView_2;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *dstop;
    QPushButton *dcontinue;
    QPushButton *ucontinue;
    QPushButton *ustop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *download)
    {
        if (download->objectName().isEmpty())
            download->setObjectName(QString::fromUtf8("download"));
        download->resize(800, 600);
        centralwidget = new QWidget(download);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        myfile = new QPushButton(centralwidget);
        myfile->setObjectName(QString::fromUtf8("myfile"));
        myfile->setGeometry(QRect(40, 240, 93, 28));
        logout = new QPushButton(centralwidget);
        logout->setObjectName(QString::fromUtf8("logout"));
        logout->setGeometry(QRect(40, 190, 93, 28));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 290, 93, 28));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 150, 41, 16));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(170, 50, 301, 491));
        tableView_2 = new QTableView(centralwidget);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        tableView_2->setGeometry(QRect(480, 50, 301, 491));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 10, 101, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        label_2->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(480, 10, 101, 31));
        label_3->setFont(font);
        dstop = new QPushButton(centralwidget);
        dstop->setObjectName(QString::fromUtf8("dstop"));
        dstop->setGeometry(QRect(270, 10, 93, 28));
        dcontinue = new QPushButton(centralwidget);
        dcontinue->setObjectName(QString::fromUtf8("dcontinue"));
        dcontinue->setGeometry(QRect(370, 10, 93, 28));
        ucontinue = new QPushButton(centralwidget);
        ucontinue->setObjectName(QString::fromUtf8("ucontinue"));
        ucontinue->setGeometry(QRect(680, 10, 93, 28));
        ustop = new QPushButton(centralwidget);
        ustop->setObjectName(QString::fromUtf8("ustop"));
        ustop->setGeometry(QRect(580, 10, 93, 28));
        download->setCentralWidget(centralwidget);
        menubar = new QMenuBar(download);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        download->setMenuBar(menubar);
        statusbar = new QStatusBar(download);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        download->setStatusBar(statusbar);

        retranslateUi(download);

        QMetaObject::connectSlotsByName(download);
    } // setupUi

    void retranslateUi(QMainWindow *download)
    {
        download->setWindowTitle(QCoreApplication::translate("download", "MainWindow", nullptr));
        myfile->setText(QCoreApplication::translate("download", "\346\210\221\347\232\204\346\226\207\344\273\266", nullptr));
        logout->setText(QCoreApplication::translate("download", "logout", nullptr));
        pushButton_3->setText(QCoreApplication::translate("download", "\344\274\240\350\276\223\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("download", "\347\224\250\346\210\267\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("download", "Download", nullptr));
        label_3->setText(QCoreApplication::translate("download", "Upload", nullptr));
        dstop->setText(QCoreApplication::translate("download", "\345\205\250\351\203\250\346\232\202\345\201\234", nullptr));
        dcontinue->setText(QCoreApplication::translate("download", "\345\205\250\351\203\250\347\273\247\347\273\255", nullptr));
        ucontinue->setText(QCoreApplication::translate("download", "\345\205\250\351\203\250\347\273\247\347\273\255", nullptr));
        ustop->setText(QCoreApplication::translate("download", "\345\205\250\351\203\250\346\232\202\345\201\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class download: public Ui_download {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOAD_H
