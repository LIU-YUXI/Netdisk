/********************************************************************************
** Form generated from reading UI file 'netdisk.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETDISK_H
#define UI_NETDISK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
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
            netdisk->setObjectName(QStringLiteral("netdisk"));
        netdisk->resize(800, 600);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        netdisk->setFont(font);
        centralwidget = new QWidget(netdisk);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        title = new QLabel(centralwidget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(370, 200, 141, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(20);
        title->setFont(font1);
        username = new QTextEdit(centralwidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(300, 270, 231, 41));
        account = new QLabel(centralwidget);
        account->setObjectName(QStringLiteral("account"));
        account->setGeometry(QRect(230, 270, 72, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(14);
        account->setFont(font2);
        passwd = new QLabel(centralwidget);
        passwd->setObjectName(QStringLiteral("passwd"));
        passwd->setGeometry(QRect(230, 340, 72, 31));
        passwd->setFont(font2);
        password = new QTextEdit(centralwidget);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(300, 340, 231, 41));
        login = new QPushButton(centralwidget);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(250, 410, 121, 41));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(12);
        login->setFont(font3);
        regist = new QPushButton(centralwidget);
        regist->setObjectName(QStringLiteral("regist"));
        regist->setGeometry(QRect(420, 410, 121, 41));
        regist->setFont(font3);
        show = new QLabel(centralwidget);
        show->setObjectName(QStringLiteral("show"));
        show->setGeometry(QRect(230, 470, 331, 61));
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(17);
        show->setFont(font4);
        show->setAlignment(Qt::AlignCenter);
        netdisk->setCentralWidget(centralwidget);
        menubar = new QMenuBar(netdisk);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        netdisk->setMenuBar(menubar);
        statusbar = new QStatusBar(netdisk);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        netdisk->setStatusBar(statusbar);

        retranslateUi(netdisk);

        QMetaObject::connectSlotsByName(netdisk);
    } // setupUi

    void retranslateUi(QMainWindow *netdisk)
    {
        netdisk->setWindowTitle(QApplication::translate("netdisk", "netdisk", Q_NULLPTR));
        title->setText(QApplication::translate("netdisk", "\347\231\273\345\275\225", Q_NULLPTR));
        account->setText(QApplication::translate("netdisk", "\350\264\246\345\217\267", Q_NULLPTR));
        passwd->setText(QApplication::translate("netdisk", "\345\257\206\347\240\201", Q_NULLPTR));
        login->setText(QApplication::translate("netdisk", "login", Q_NULLPTR));
        regist->setText(QApplication::translate("netdisk", "regist", Q_NULLPTR));
        show->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class netdisk: public Ui_netdisk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDISK_H
