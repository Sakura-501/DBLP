#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon("images/icon.ico"));
    this->setWindowTitle("登录窗口");
//    QPalette PAllbackground = this->palette();
//    QImage ImgAllbackground(":/new/prefix1/images/1.jpg");
//    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
//    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
//    this->setPalette(PAllbackground);


    //点击登录窗口的退出按钮结束进程
    connect(ui->quit,&QPushButton::clicked,[=](){
        //点击退出按钮会弹出警告！
        if(QMessageBox::Yes == QMessageBox::question(this,"警告","确定退出系统？",
                                                     QMessageBox::Yes|QMessageBox::No))
        {
                this->close();

        }
    });

    //点击登录窗口的登录按钮进行登录
    connect(ui->login,&QPushButton::clicked,[=](){
        //设置里两个账号密码
        if((ui->usernameinput->text()=="root"&&ui->passwordinput->text()=="root")||
                (ui->usernameinput->text()=="admin"&&ui->passwordinput->text()=="123456"))
       {
            this->close();//登录窗口关闭
            //w.show();//主窗口打开

            //登录成功，主登录窗口下的成员对象菜单窗口就可以打开。
            m.show();

        }
        else
        {
            QMessageBox::critical(this,"警告","账号或密码输入有误，请重新输入！");
        }
//        this->close();
//        m.show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

