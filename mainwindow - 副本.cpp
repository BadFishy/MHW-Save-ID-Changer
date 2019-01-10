#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QMessageBox>
#include <QTextCodec>

char step=0;
char text[8];
char text2[8];
char text3[8];
char jiaoyan[2];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    this->setWindowTitle(QString("MHW Save ID Changer v0.4"));
    this->setAutoFillBackground(true);//开启背景设置
    this->setPalette(QPalette(QColor(255,255,255)));
    //ui->pushButton->setStyleSheet("background-color: rgb(255,255,255)");


}

MainWindow::~MainWindow()
{
    delete ui;

}


bool fuc_jiaoyan()
{
    if(jiaoyan[0]!=0x33){

        return 1;
    }
    if(jiaoyan[1]!=0x21){

        return 1;
    }
    return 0;
}



void MainWindow::on_pushButton_clicked()
{


    if(step==0){
        QMessageBox mesg;
        mesg.warning(this,"注意","只支持STEAM之间更换存档！   ");

        QString file_full;
       QFileInfo fi;//文件路径
       file_full = QFileDialog::getOpenFileName(this, tr("选择自己的存档"),
                                                "./", tr("存档文件 (SAVEDATA1000) (SAVEDATA1000);;所有文件 (*.*)"));
       QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
       std::string str = code->fromUnicode(file_full).data();

       const char* str1 = str.c_str();

       if(strlen(str1)<1)
       {
           QMessageBox mesg;
           mesg.warning(this,"警告","未选择文件！   ");
           return;
       }

       //ui->label->setText(str1);
       FILE * fp1;
       fp1 = fopen(str1,"rb");
       if(fp1==NULL){
           QMessageBox mesg;
           mesg.critical(this,"错误","打开“自己的存档”失败！   ");
           fclose(fp1);
           return;
       }

       fseek(fp1,32,SEEK_SET);//判断是否是MHW的存档文件
       fgets(jiaoyan,9,fp1);
       if(fuc_jiaoyan()==1){
           QMessageBox mesg;
           mesg.critical(this,"错误","选择的不是MHW的存档文件！   ");
           fclose(fp1);
           return;
       }

       fseek(fp1,40,SEEK_SET);
       fgets(text,9,fp1);
       fclose(fp1);

       mesg.about(this,"提示","提取成功！   ");
       ui->label->setText("已提取自己存档的ID\n\n请点击按钮进行下一步");
       ui->pushButton->setText("2.选择“别人的存档”");
       step++;
       return;
    }

    if(step==1){
        QString file_full;
       QFileInfo fi;//文件路径
       file_full = QFileDialog::getOpenFileName(this, tr("选择别人的存档"),
                                                "./", tr("存档文件 (SAVEDATA1000) (SAVEDATA1000);;所有文件 (*.*)"));
       QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
       std::string str = code->fromUnicode(file_full).data();
       const char* str2 = str.c_str();

       if(strlen(str2)<1)
       {
           QMessageBox mesg;
           mesg.warning(this,"警告","未选择文件！   ");
           return;
       }

       FILE * fp2;
       fp2 = fopen(str2,"r+");
       if(fp2==NULL){
           QMessageBox mesg;
           mesg.critical(this,"错误","打开“别人的存档”失败！   ");
           fclose(fp2);
           return;
       }

       fseek(fp2,32,SEEK_SET);//判断是否是MHW的存档文件
       fgets(jiaoyan,9,fp2);
       if(fuc_jiaoyan()==1){
           QMessageBox mesg;
           mesg.critical(this,"错误","选择的不是MHW的存档文件！   ");
           fclose(fp2);
           return;
       }


       fseek(fp2,40,SEEK_SET);
       fgets(text2,9,fp2);

       for(int i=0; i<8; i++){
           if(text[i]==text2[i]){
                QMessageBox mesg;
                mesg.critical(this,"错误","选择的两个存档的ID相同！   ");
                fclose(fp2);
                return;
           }
       }


       fseek(fp2,40,SEEK_SET);
       fwrite(text,8,1,fp2);


       fclose(fp2);
       FILE * fp3;
       fp3 = fopen(str2,"rb");
       fseek(fp3,40,SEEK_SET);
       fgets(text3,8,fp3);
       fclose(fp3);
       for(int i=0; i<8; i++){
           if(text[i]!=text3[i]){
                QMessageBox mesg;
                mesg.critical(this,"错误","处理失败！\n存档的ID没有被正确的改变。   ");
                return;
           }
       }
       QMessageBox mesg;
       mesg.about(this,"提示","处理成功！   ");
       ui->label->setText("存档ID改签成功！\n\n现在您可以把别人的存档覆盖到您的存档目录了\n\n记得备份自己的存档哦~");
       ui->pushButton->setText("关闭");
       step++;
       return;

    }

    if(step==2){
        this->close();
    }

    //      打开文件        获取文件路径
    //     file_full = QFileDialog::getSaveFileName(this,tr("Save File"),tr("*.txt"));
    //      保存文件        获取文件路径  “Save File” 对话框名        “*.txt” 默认文件名
    //   fi= QFileInfo(file_full);


}
