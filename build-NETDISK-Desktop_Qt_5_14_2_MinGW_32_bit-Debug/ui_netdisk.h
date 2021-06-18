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
    QLabel *label;
    QTextEdit *textEdit;
    QLabel *label_2;
    QLabel *label_3;
    QTextEdit *textEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
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
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 200, 81, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(20);
        label->setFont(font1);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(300, 270, 231, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 270, 72, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(14);
        label_2->setFont(font2);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(230, 340, 72, 31));
        label_3->setFont(font2);
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(300, 340, 231, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(250, 410, 121, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(12);
        pushButton->setFont(font3);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(420, 410, 121, 41));
        pushButton_2->setFont(font3);
        netdisk->setCentralWidget(centralwidget);
        menubar = new QMenuBar(netdisk);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
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
        label->setText(QCoreApplication::translate("netdisk", "\347\231\273\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("netdisk", "\350\264\246\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("netdisk", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("netdisk", "login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("netdisk", "regist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class netdisk: public Ui_netdisk {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDISK_H
