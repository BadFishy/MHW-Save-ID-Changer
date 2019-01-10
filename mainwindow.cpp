#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QMessageBox>
#include <QTextCodec>

char step=0;
char text[9];
char text2[9];
char text3[9];
char jiaoyan[2];
bool Auto = 0;

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

        if(Auto==1){
            //aaaaaaaaaa
        }

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

        mesg.about(this,"提示","提取成功！   ");
        ui->label->setText("已提取自己存档的ID\n\n请点击按钮进行下一步");
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
        mesg.about(this,"重要提示","开启这个选项后   \n选择“自己的存档”时请直接选择游戏存档目录的存档   \n"
                            "游戏存档路径在   \n“你Steam的安装目录\\userdata\\ {你的STEAM识别码} \\582010\\remote”    \n\n"
                               "程序将自动把你“自己的存档”替换成“别人的存档”   \n"
                             "即处理完成后直接进游戏就是别人的存档了   \n程序也会同时在该目录下备份您之前的存档   \n");
        Auto = 1;
        return;
    }
    Auto = 0;
    return;

}
