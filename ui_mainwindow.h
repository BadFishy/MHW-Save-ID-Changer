/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionreadme;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *checkBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(381, 237);
        MainWindow->setMinimumSize(QSize(381, 237));
        MainWindow->setMaximumSize(QSize(381, 237));
        actionreadme = new QAction(MainWindow);
        actionreadme->setObjectName(QString::fromUtf8("actionreadme"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(170, 180, 181, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 381, 121));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 140, 221, 20));
        lineEdit->setAlignment(Qt::AlignCenter);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(true);
        checkBox->setGeometry(QRect(50, 180, 101, 31));
        checkBox->setCheckable(true);
        checkBox->setChecked(false);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        actionreadme->setText(QApplication::translate("MainWindow", "readme", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "1.\351\200\211\346\213\251\342\200\234\350\207\252\345\267\261\347\232\204\345\255\230\346\241\243\342\200\235", nullptr));
        label->setText(QApplication::translate("MainWindow", "MHW \345\255\230\346\241\243\346\224\271\347\255\276\345\267\245\345\205\267 v1.0\n"
"\n"
"\347\224\250\344\272\216STEAM\344\270\215\345\220\214\350\264\246\345\217\267\344\271\213\351\227\264\347\232\204\345\255\230\346\241\243\346\233\277\346\215\242\n"
"\n"
"by.\345\235\217\351\261\274\347\202\222\345\271\264\347\263\225\n"
"\n"
"2019.01.10", nullptr));
        lineEdit->setText(QApplication::translate("MainWindow", "\344\275\240\342\200\234\350\207\252\345\267\261\347\232\204\345\255\230\346\241\243\342\200\235\347\232\204ID\345\260\206\346\230\276\347\244\272\345\234\250\350\277\231\351\207\214", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\346\233\277\346\215\242\345\255\230\346\241\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H