/********************************************************************************
** Form generated from reading UI file 'dialog_folder.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FOLDER_H
#define UI_DIALOG_FOLDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog_folder
{
public:
    QPushButton *logout;
    QTextBrowser *textBrowser;
    QPushButton *filearray;
    QLabel *label;
    QPushButton *myfile;
    QPushButton *link;
    QPushButton *unlink;
    QPushButton *addpath;
    QPushButton *deletepath;
    QPushButton *confirm;
    QPlainTextEdit *cloudpath;
    QPlainTextEdit *localpath;

    void setupUi(QDialog *Dialog_folder)
    {
        if (Dialog_folder->objectName().isEmpty())
            Dialog_folder->setObjectName(QString::fromUtf8("Dialog_folder"));
        Dialog_folder->setEnabled(true);
        Dialog_folder->resize(800, 758);
        logout = new QPushButton(Dialog_folder);
        logout->setObjectName(QString::fromUtf8("logout"));
        logout->setGeometry(QRect(20, 200, 121, 28));
        textBrowser = new QTextBrowser(Dialog_folder);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(160, 20, 611, 531));
        filearray = new QPushButton(Dialog_folder);
        filearray->setObjectName(QString::fromUtf8("filearray"));
        filearray->setGeometry(QRect(20, 300, 121, 28));
        label = new QLabel(Dialog_folder);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 145, 71, 31));
        myfile = new QPushButton(Dialog_folder);
        myfile->setObjectName(QString::fromUtf8("myfile"));
        myfile->setGeometry(QRect(20, 250, 121, 28));
        link = new QPushButton(Dialog_folder);
        link->setObjectName(QString::fromUtf8("link"));
        link->setGeometry(QRect(200, 580, 111, 51));
        unlink = new QPushButton(Dialog_folder);
        unlink->setObjectName(QString::fromUtf8("unlink"));
        unlink->setGeometry(QRect(340, 580, 111, 51));
        addpath = new QPushButton(Dialog_folder);
        addpath->setObjectName(QString::fromUtf8("addpath"));
        addpath->setGeometry(QRect(480, 580, 141, 51));
        deletepath = new QPushButton(Dialog_folder);
        deletepath->setObjectName(QString::fromUtf8("deletepath"));
        deletepath->setGeometry(QRect(650, 580, 131, 51));
        confirm = new QPushButton(Dialog_folder);
        confirm->setObjectName(QString::fromUtf8("confirm"));
        confirm->setEnabled(false);
        confirm->setGeometry(QRect(670, 660, 111, 51));
        cloudpath = new QPlainTextEdit(Dialog_folder);
        cloudpath->setObjectName(QString::fromUtf8("cloudpath"));
        cloudpath->setEnabled(false);
        cloudpath->setGeometry(QRect(160, 650, 461, 41));
        localpath = new QPlainTextEdit(Dialog_folder);
        localpath->setObjectName(QString::fromUtf8("localpath"));
        localpath->setEnabled(false);
        localpath->setGeometry(QRect(160, 710, 461, 41));

        retranslateUi(Dialog_folder);

        QMetaObject::connectSlotsByName(Dialog_folder);
    } // setupUi

    void retranslateUi(QDialog *Dialog_folder)
    {
        Dialog_folder->setWindowTitle(QCoreApplication::translate("Dialog_folder", "Dialog", nullptr));
        logout->setText(QCoreApplication::translate("Dialog_folder", "logout", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Dialog_folder", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\231\346\230\257\346\230\276\347\244\272\346\226\207\344\273\266\345\244\271\345\222\214\346\226\207\344\273\266\347\232\204\345\234\260\346\226\271\357\274\214\344\275\240\351\232\217\344\276\277\346\224\271\357\274\214\346\210\221\345\217\252\346\230\257\345\234\250\350\277\231\351\207\214\345\234\210\344\270\252\345\234\260\346\226\271</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\202\271\342\200\234\346\210\221\347\232\204\346\226\207\344\273\266\342\200\235\346\230\276"
                        "\347\244\272\347\232\204\346\230\257\350\277\231\344\270\252\347\225\214\351\235\242\357\274\214\347\202\271\344\274\240\350\276\223\345\210\227\350\241\250\357\274\214\350\267\263\345\210\260\345\217\246\345\244\226\344\270\200\344\270\252</p></body></html>", nullptr));
        filearray->setText(QCoreApplication::translate("Dialog_folder", "\344\274\240\350\276\223\345\210\227\350\241\250", nullptr));
        label->setText(QCoreApplication::translate("Dialog_folder", "\347\224\250\346\210\267\357\274\232", nullptr));
        myfile->setText(QCoreApplication::translate("Dialog_folder", "\346\210\221\347\232\204\346\226\207\344\273\266", nullptr));
        link->setText(QCoreApplication::translate("Dialog_folder", "\347\273\221\345\256\232\347\233\256\345\275\225", nullptr));
        unlink->setText(QCoreApplication::translate("Dialog_folder", "\350\247\243\347\273\221\347\233\256\345\275\225", nullptr));
        addpath->setText(QCoreApplication::translate("Dialog_folder", "\345\242\236\345\212\240\344\272\221\347\233\256\345\275\225", nullptr));
        deletepath->setText(QCoreApplication::translate("Dialog_folder", "\345\210\240\351\231\244\344\272\221\347\233\256\345\275\225", nullptr));
        confirm->setText(QCoreApplication::translate("Dialog_folder", "\347\241\256\345\256\232", nullptr));
        cloudpath->setPlainText(QCoreApplication::translate("Dialog_folder", "cloudpath", nullptr));
        localpath->setPlainText(QCoreApplication::translate("Dialog_folder", "localpath", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_folder: public Ui_Dialog_folder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FOLDER_H
