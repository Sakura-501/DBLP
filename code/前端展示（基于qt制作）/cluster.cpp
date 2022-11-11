#include "cluster.h"
#include "ui_cluster.h"
#include <fstream>
#include <QHeaderView>
#include <QString>
#include <QProgressBar>
#include <stdlib.h>
#include <sstream>
#include <QDebug>
#include<QDir>
//#include<iostream>
using namespace std;

//string int2str(int int_temp)
//{
//    string string_temp;
//    stringstream stream;
//    stream<<int_temp;
//    stream>>string_temp;
//    return string_temp;
//}

Cluster::Cluster(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cluster)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(1); //设置列数
    ui->tableWidget->setRowCount(114);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
        ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
        QStringList header;
        header<<tr("k阶子图数量");
        ui->tableWidget->setHorizontalHeaderLabels(header);
        string temp_name,temp_fre;
        ifstream infile("D:\\xmlhomework\\qtwork\\qtxml\\resource\\cluster.txt", ios::in);
        for(int i=0;i<114;i++)
        {
            getline(infile,temp_name);
            //getline(infile,temp_fre);
            //qDebug()<<QString::fromStdString(temp_name)<<QString::fromStdString(temp_fre);
//            int pos=temp_name.find("\r");
//            temp_name=temp_name.erase(pos);
    //        qDebug()<<pos<<QString::fromStdString(temp_name)<<QString::fromStdString(temp_fre);
            //ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::fromStdString(int2str(i+1))));
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::fromStdString(temp_name)));
            //ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::fromStdString(temp_fre)));
        }
}

Cluster::~Cluster()
{
    delete ui;
}
