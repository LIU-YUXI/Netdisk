/********************************************************************************
** Form generated from reading UI file 'netdisk.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETDISK_H
#define UI_NETDISK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_netdisk
{
public:
    QWidget *centralwidget;
    QLabel *title;
    QTextEdit *username;
    QLabel *account;
    QLabel *passwd;
    QTextEdit *password;
    QPushButton *login;
    QPushButton *regist;
    QLabel *show;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *netdisk)
    {
        if (netdisk->objectName().isEmpty())
            netdisk->setObjectName(QString::fromUtf8("netdisk"));
        netdisk->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        netdisk->setFont(font);
        centralwidget = new QWidget(netdisk);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(370, 200, 141, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(20);
        title->setFont(font1);
        username = new QTextEdit(centralwidget);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(300, 270, 231, 41));
        account = new QLabel(centralwidget);
        account->setObjectName(QString::fromUtf8("account"));
        account->setGeometry(QRect(230, 270, 72, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(14);
        account->setFont(font2);
        passwd = new QLabel(centralwidget);
        passwd->setObjectName(QString::fromUtf8("passwd"));
        passwd->setGeometry(QRect(230, 340, 72, 31));
        passwd->setFont(font2);
        password = new QTextEdit(centralwidget);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(300, 340, 231, 41));
        login = new QPushButton(centralwidget);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(250, 410, 121, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        login->setFont(font3);
        regist = new QPushButton(centralwidget);
        regist->setObjectName(QString::fromUtf8("regist"));
        regist->setGeometry(QRect(420, 410, 121, 41));
        regist->setFont(font3);
        show = new QLabel(centralwidget);
        show->setObjectName(QString::fromUtf8("show"));
        show->setGeometry(QRect(230, 470, 331, 61));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(17);
        show->setFont(font4);
        show->setAlignment(Qt::AlignCenter);
        netdisk->setCentralWidget(centralwidget);
        menubar = new QMenuBar(netdisk);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        netdisk->setMenuBar(menubar);
        statusbar = new QStatusBar(netdisk);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        netdisk->setStatusBar(statusbar);

        retranslateUi(netdisk);

        QMetaObject::connectSlotsByName(netdisk);
    } // setupUi

    void retranslateUi(QMainWindow *netdisk)
    {
        netdisk->setWindowTitle(QCoreApplication::translate("netdisk", "netdisk", nullptr));
        title->setText(QCoreApplication::translate("netdisk", "\347\231\273\345\275\225", nullptr));
        account->setText(QCoreApplication::translate("netdisk", "\350\264\246\345\217\267", nullptr));
        passwd->setText(QCoreApplication::translate("netdisk", "\345\257\206\347\240\201", nullptr));
        login->setText(QCoreApplication::translate("netdisk", "login", nullptr));
        regist->setText(QCoreApplication::translate("netdisk", "regist", nullptr));
        show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class netdisk: public Ui_netdisk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDISK_H
