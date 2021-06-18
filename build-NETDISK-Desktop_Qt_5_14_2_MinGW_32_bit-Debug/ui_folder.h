/********************************************************************************
** Form generated from reading UI file 'folder.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOLDER_H
#define UI_FOLDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_folder
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextBrowser *textBrowser;
    QPushButton *logout;
    QPushButton *myfile;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *folder)
    {
        if (folder->objectName().isEmpty())
            folder->setObjectName(QString::fromUtf8("folder"));
        folder->resize(800, 600);
        centralwidget = new QWidget(folder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 150, 41, 16));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(170, 10, 611, 531));
        logout = new QPushButton(centralwidget);
        logout->setObjectName(QString::fromUtf8("logout"));
        logout->setGeometry(QRect(40, 190, 93, 28));
        myfile = new QPushButton(centralwidget);
        myfile->setObjectName(QString::fromUtf8("myfile"));
        myfile->setGeometry(QRect(40, 240, 93, 28));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 290, 93, 28));
        folder->setCentralWidget(centralwidget);
        menubar = new QMenuBar(folder);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        folder->setMenuBar(menubar);
        statusbar = new QStatusBar(folder);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        folder->setStatusBar(statusbar);

        retranslateUi(folder);

        QMetaObject::connectSlotsByName(folder);
    } // setupUi

    void retranslateUi(QMainWindow *folder)
    {
        folder->setWindowTitle(QCoreApplication::translate("folder", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("folder", "\347\224\250\346\210\267\357\274\232", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("folder", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\231\346\230\257\346\230\276\347\244\272\346\226\207\344\273\266\345\244\271\345\222\214\346\226\207\344\273\266\347\232\204\345\234\260\346\226\271\357\274\214\344\275\240\351\232\217\344\276\277\346\224\271\357\274\214\346\210\221\345\217\252\346\230\257\345\234\250\350\277\231\351\207\214\345\234\210\344\270\252\345\234\260\346\226\271</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\202\271\342\200\234\346\210\221\347\232\204\346\226\207\344\273\266\342\200\235\346\230\276"
                        "\347\244\272\347\232\204\346\230\257\350\277\231\344\270\252\347\225\214\351\235\242\357\274\214\347\202\271\344\274\240\350\276\223\345\210\227\350\241\250\357\274\214\350\267\263\345\210\260\345\217\246\345\244\226\344\270\200\344\270\252</p></body></html>", nullptr));
        logout->setText(QCoreApplication::translate("folder", "logout", nullptr));
        myfile->setText(QCoreApplication::translate("folder", "\346\210\221\347\232\204\346\226\207\344\273\266", nullptr));
        pushButton_3->setText(QCoreApplication::translate("folder", "\344\274\240\350\276\223\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class folder: public Ui_folder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOLDER_H
