/********************************************************************************
** Form generated from reading UI file 'dialog_regist.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_REGIST_H
#define UI_DIALOG_REGIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_Dialog_regist
{
public:
    QLabel *label_2;
    QTextEdit *account;
    QTextEdit *username;
    QTextEdit *password1;
    QTextEdit *password2;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_4;
    QPushButton *finish;
    QLabel *msg;

    void setupUi(QDialog *Dialog_regist)
    {
        if (Dialog_regist->objectName().isEmpty())
            Dialog_regist->setObjectName(QString::fromUtf8("Dialog_regist"));
        Dialog_regist->resize(800, 600);
        label_2 = new QLabel(Dialog_regist);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(230, 240, 72, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label_2->setFont(font);
        account = new QTextEdit(Dialog_regist);
        account->setObjectName(QString::fromUtf8("account"));
        account->setGeometry(QRect(300, 240, 231, 41));
        username = new QTextEdit(Dialog_regist);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(300, 170, 231, 41));
        password1 = new QTextEdit(Dialog_regist);
        password1->setObjectName(QString::fromUtf8("password1"));
        password1->setGeometry(QRect(300, 310, 231, 41));
        password2 = new QTextEdit(Dialog_regist);
        password2->setObjectName(QString::fromUtf8("password2"));
        password2->setGeometry(QRect(300, 380, 231, 41));
        label_3 = new QLabel(Dialog_regist);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(230, 310, 72, 31));
        label_3->setFont(font);
        label_5 = new QLabel(Dialog_regist);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(220, 170, 72, 31));
        label_5->setFont(font);
        label = new QLabel(Dialog_regist);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(370, 90, 81, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(20);
        label->setFont(font1);
        label_4 = new QLabel(Dialog_regist);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(200, 380, 101, 31));
        label_4->setFont(font);
        finish = new QPushButton(Dialog_regist);
        finish->setObjectName(QString::fromUtf8("finish"));
        finish->setGeometry(QRect(340, 460, 121, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        finish->setFont(font2);
        msg = new QLabel(Dialog_regist);
        msg->setObjectName(QString::fromUtf8("msg"));
        msg->setGeometry(QRect(180, 550, 431, 31));
        msg->setFont(font);
        msg->setAlignment(Qt::AlignCenter);

        retranslateUi(Dialog_regist);

        QMetaObject::connectSlotsByName(Dialog_regist);
    } // setupUi

    void retranslateUi(QDialog *Dialog_regist)
    {
        Dialog_regist->setWindowTitle(QCoreApplication::translate("Dialog_regist", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_regist", "\350\264\246\345\217\267", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_regist", "\345\257\206\347\240\201", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog_regist", "\347\224\250\346\210\267\345\220\215", nullptr));
        label->setText(QCoreApplication::translate("Dialog_regist", "\346\263\250\345\206\214", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog_regist", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        finish->setText(QCoreApplication::translate("Dialog_regist", "Finish", nullptr));
        msg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog_regist: public Ui_Dialog_regist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_REGIST_H
