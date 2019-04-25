#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>


int main(int argc, char *argv[])
{
    int code = 1,exit = 1;


    while(exit != 0){
        if(code == 2){
            QApplication a(argc, argv);
            QTranslator m_Translator;
                m_Translator.load("en.qm");
                qApp->installTranslator(&m_Translator);
                code = 1;
                MainWindow w;
                w.show();
                exit = a.exec();
        }
        else if(code == 1){
            QApplication a(argc, argv);
            code = 2;
            MainWindow w;
            w.show();
            exit = a.exec();
        }

    }




    return code;
}
