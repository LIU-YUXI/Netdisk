/********************************************************************************
** Form generated from reading UI file 'dialog_download.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DOWNLOAD_H
#define UI_DIALOG_DOWNLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Dialog_download
{
public:
    QPushButton *logout;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_3;
    QLabel *label;
    QPushButton *myfile;

    void setupUi(QDialog *Dialog_download)
    {
        if (Dialog_download->objectName().isEmpty())
            Dialog_download->setObjectName(QStringLiteral("Dialog_download"));
        Dialog_download->resize(800, 600);
        logout = new QPushButton(Dialog_download);
        logout->setObjectName(QStringLiteral("logout"));
        logout->setGeometry(QRect(30, 200, 93, 28));
        textBrowser = new QTextBrowser(Dialog_download);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(160, 20, 611, 531));
        pushButton_3 = new QPushButton(Dialog_download);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 300, 93, 28));
        label = new QLabel(Dialog_download);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 160, 41, 16));
        myfile = new QPushButton(Dialog_download);
        myfile->setObjectName(QStringLiteral("myfile"));
        myfile->setGeometry(QRect(30, 250, 93, 28));

        retranslateUi(Dialog_download);

        QMetaObject::connectSlotsByName(Dialog_download);
    } // setupUi

    void retranslateUi(QDialog *Dialog_download)
    {
        Dialog_download->setWindowTitle(QApplication::translate("Dialog_download", "Dialog", Q_NULLPTR));
        logout->setText(QApplication::translate("Dialog_download", "logout", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("Dialog_download", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\231\346\230\257\346\230\276\347\244\272\346\226\207\344\273\266\345\244\271\345\222\214\346\226\207\344\273\266\347\232\204\345\234\260\346\226\271\357\274\214\344\275\240\351\232\217\344\276\277\346\224\271\357\274\214\346\210\221\345\217\252\346\230\257\345\234\250\350\277\231\351\207\214\345\234\210\344\270\252\345\234\260\346\226\271</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\202\271\342\200\234\346\210\221\347\232\204\346\226\207\344\273\266\342\200\235\346\230\276"
                        "\347\244\272\347\232\204\346\230\257\350\277\231\344\270\252\347\225\214\351\235\242\357\274\214\347\202\271\344\274\240\350\276\223\345\210\227\350\241\250\357\274\214\350\267\263\345\210\260\345\217\246\345\244\226\344\270\200\344\270\252</p></body></html>", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Dialog_download", "\344\274\240\350\276\223\345\210\227\350\241\250", Q_NULLPTR));
        label->setText(QApplication::translate("Dialog_download", "\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        myfile->setText(QApplication::translate("Dialog_download", "\346\210\221\347\232\204\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Dialog_download: public Ui_Dialog_download {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DOWNLOAD_H
