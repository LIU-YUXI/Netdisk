/********************************************************************************
** Form generated from reading UI file 'dialog_regist.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_REGIST_H
#define UI_DIALOG_REGIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
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
            Dialog_regist->setObjectName(QStringLiteral("Dialog_regist"));
        Dialog_regist->resize(800, 600);
        label_2 = new QLabel(Dialog_regist);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(230, 240, 72, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(14);
        label_2->setFont(font);
        account = new QTextEdit(Dialog_regist);
        account->setObjectName(QStringLiteral("account"));
        account->setGeometry(QRect(300, 240, 231, 41));
        username = new QTextEdit(Dialog_regist);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(300, 170, 231, 41));
        password1 = new QTextEdit(Dialog_regist);
        password1->setObjectName(QStringLiteral("password1"));
        password1->setGeometry(QRect(300, 310, 231, 41));
        password2 = new QTextEdit(Dialog_regist);
        password2->setObjectName(QStringLiteral("password2"));
        password2->setGeometry(QRect(300, 380, 231, 41));
        label_3 = new QLabel(Dialog_regist);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(230, 310, 72, 31));
        label_3->setFont(font);
        label_5 = new QLabel(Dialog_regist);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 170, 72, 31));
        label_5->setFont(font);
        label = new QLabel(Dialog_regist);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(370, 90, 81, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(20);
        label->setFont(font1);
        label_4 = new QLabel(Dialog_regist);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(200, 380, 101, 31));
        label_4->setFont(font);
        finish = new QPushButton(Dialog_regist);
        finish->setObjectName(QStringLiteral("finish"));
        finish->setGeometry(QRect(340, 460, 121, 41));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        finish->setFont(font2);
        msg = new QLabel(Dialog_regist);
        msg->setObjectName(QStringLiteral("msg"));
        msg->setGeometry(QRect(180, 550, 431, 31));
        msg->setFont(font);
        msg->setAlignment(Qt::AlignCenter);

        retranslateUi(Dialog_regist);

        QMetaObject::connectSlotsByName(Dialog_regist);
    } // setupUi

    void retranslateUi(QDialog *Dialog_regist)
    {
        Dialog_regist->setWindowTitle(QApplication::translate("Dialog_regist", "Dialog", Q_NULLPTR));
        label_2->setText(QApplication::translate("Dialog_regist", "\350\264\246\345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("Dialog_regist", "\345\257\206\347\240\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("Dialog_regist", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog_regist", "\346\263\250\345\206\214", Q_NULLPTR));
        label_4->setText(QApplication::translate("Dialog_regist", "\347\241\256\350\256\244\345\257\206\347\240\201", Q_NULLPTR));
        finish->setText(QApplication::translate("Dialog_regist", "Finish", Q_NULLPTR));
        msg->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Dialog_regist: public Ui_Dialog_regist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_REGIST_H
