#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QMessageBox>
#include <QTextCodec>
#include <QString>
#include <QFileInfo>

char step=0;
char text[9];
char text2[9];
char text3[9];
char jiaoyan[2];
bool Auto;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle(QString("MHW Save ID Changer v1.0"));
    this->setAutoFillBackground(true);//开启背景设置
    //this->setPalette(QPalette(QColor(255,255,255)));
    ui->label->setStyleSheet("background-color: rgb(255,255,255)");


}

MainWindow::~MainWindow()
{
    delete ui;

}


bool fuc_jiaoyan()
{
    if(jiaoyan[0]!=0x33)
    {
        return 1;
    }
    if(jiaoyan[1]!=0x21)
    {
        return 1;
    }
    return 0;
}



void MainWindow::on_pushButton_clicked()
{


    if(step==0)
    {

        QMessageBox mesg;
        mesg.warning(this,"注意","只支持STEAM之间更换存档！   ");

        QString file_full;
        QFileInfo fi;//文件路径
        if(ui->checkBox->isChecked()==true){ //ui->checkBox->isChecked()==true 判断是否是开启“自动替换存档”功能
            file_full = QFileDialog::getOpenFileName(this, tr("选择自己的存档"),
                        "./", tr("存档文件 (SAVEDATA1000) (SAVEDATA1000)"));
        }
        else{
            file_full = QFileDialog::getOpenFileName(this, tr("选择自己的存档"),
                        "./", tr("存档文件 (SAVEDATA1000) (SAVEDATA1000);;所有文件 (*.*)"));
        }

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
        if(fp1==NULL)
        {
            QMessageBox mesg;
            mesg.critical(this,"错误","打开“自己的存档”失败！   ");
            fclose(fp1);
            return;
        }

        fseek(fp1,32,SEEK_SET);//判断是否是MHW的存档文件
        fgets(jiaoyan,3,fp1);
        if(fuc_jiaoyan()==1)
        {
            QMessageBox mesg;
            mesg.critical(this,"错误","选择的不是MHW的存档文件！   ");
            fclose(fp1);
            return;
        }


        if(ui->checkBox->isChecked()==true){
            //ui->lineEdit->setText(file_full);

            bool rx = file_full.contains("582010"); //成功返回true  第二个参数表示是否大小写敏感
            if(rx != true){
                QMessageBox mesg;
                mesg.critical(this,"错误","选择的目录不是游戏存档目录！   ");
                QMessageBox mesg1;
                mesg1.about(this,"重要提示","\n开启“自动替换存档”选项后   \n选择“自己的存档”时请直接选择游戏存档目录的存档   \n"
                                    "游戏存档路径在   \n“Steam安装目录\\userdata\\{你的账号识别码}\\582010\\remote”    \n\n"
                                       "程序将自动把你“自己的存档”替换成“别人的存档”   \n"
                                     "即处理完成后直接进游戏就是别人的存档了   \n程序也会同时在该目录下备份您之前的存档   \n");
                QMessageBox mesg2;
                mesg1.about(this,"重要提示","\n请重新选择存档目录   \n或者关闭“自动替换存档”，改签后自行替换存档   \n");
                return;
            }
        }
        bool ok;
        if(ui->checkBox->isChecked()==true){
            QString path1 = file_full;
            QString path2 = QString("%1_backup").arg(file_full);
            QFileInfo file(path2); //判断是否已经有备份
            for(int i=1;;i++){
                path2 = QString("%1_backup%2").arg(file_full).arg(i);
                //mesg.about(this,"提示",path2);
                //return;
                QFileInfo file(path2); //判断是否已经有备份
                if(file.exists()==false)
                {
                    break;
                }

            }
            ok = QFile::copy(path1,path2);
        }

        ui->checkBox->setEnabled(false); //禁止调整 “自动替换存档”选项



        memset(text,0x00,sizeof(text));
        fseek(fp1,40,SEEK_SET);

        fread(text,8,1,fp1);
        QString strr;
        fclose(fp1);
        char buffer[100];
        memset(buffer, 0x00, sizeof(buffer));
        sprintf(buffer, "%02X %02X %02X %02X %02X %02X %02X %02X", text[0]&0xff,text[1]&0xff, text[2]&0xff,text[3]&0xff, text[4]&0xff, text[5]&0xff, text[6]&0xff, text[7]&0xff);
        strr = QString("%1").arg(buffer);
        ui->lineEdit->setText(strr);





            if(ok == true && ui->checkBox->isChecked()==true){
                mesg.about(this,"提示","提取并备份成功！   ");
                ui->label->setText("已备份自己的存档，已提取自己存档的ID\n\n请点击按钮进行下一步");
            }
            else if(ok != true && ui->checkBox->isChecked()==true){
                mesg.critical(this,"错误","备份失败！\n请检查游戏是否关闭，是否有其他程序占用存档文件   \n");
            return;

        }
            else{
                mesg.about(this,"提示","提取成功！   ");
                ui->label->setText("已提取自己存档的ID\n\n请点击按钮进行下一步");
            }



        ui->pushButton->setText("2.选择“别人的存档”");
        step++;
        return;
    }

    if(step==1)
    {
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
        fp2 = fopen(str2,"rb+");
        if(fp2==NULL)
        {
            QMessageBox mesg;
            mesg.critical(this,"错误","打开“别人的存档”失败！   ");
            fclose(fp2);
            return;
        }

        fseek(fp2,32,SEEK_SET);//判断是否是MHW的存档文件
        fgets(jiaoyan,3,fp2);
        if(fuc_jiaoyan()==1)
        {
            QMessageBox mesg;
            mesg.critical(this,"错误","选择的不是MHW的存档文件！   ");
            fclose(fp2);
            return;
        }


        fseek(fp2,40,SEEK_SET);
        fread(text2,8,1,fp2);
        ;
        for(int i=0, idsame = 0; i<8; i++)
        {
            if(text[i]==text2[i])
            {
                idsame++;
            }
            if(idsame>=8)
            {
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
        fread(text3,8,1,fp3);
        fclose(fp3);
        for(int i=0; i<8; i++)
        {
            if(text[i]!=text3[i])
            {
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

    if(step==2)
    {
        this->close();
    }

    //打开文件        获取文件路径
    //file_full = QFileDialog::getSaveFileName(this,tr("Save File"),tr("*.txt"));
    //保存文件        获取文件路径  “Save File” 对话框名        “*.txt” 默认文件名
    //fi= QFileInfo(file_full);


}




void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 != 0){
        QMessageBox mesg;
        mesg.about(this,"重要提示","\n开启这个选项后   \n选择“自己的存档”时请直接选择游戏存档目录的存档   \n"
                            "游戏存档路径在   \n“Steam安装目录\\userdata\\{你的账号识别码}\\582010\\remote”    \n\n"
                               "程序将自动把你“自己的存档”替换成“别人的存档”   \n"
                             "即处理完成后直接进游戏就是别人的存档了   \n程序也会同时在该目录下备份您之前的存档   \n");

    }

    return;

}
