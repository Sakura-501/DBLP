#ifndef SHOW_DETAIL_H
#define SHOW_DETAIL_H

#include <QDialog>
#include <string>
#include <set>
#include <QXmlStreamReader>
#include <QtGui>
#include <QDrag>
#include "QTextStream"
#include <QIcon>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTime>
#include <sstream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include<bits/stdc++.h>
#include<fstream>
#include <string>
#include <set>
#include <QXmlStreamReader>
#include <QtGui>
#include <QDrag>
#include <QIcon>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTime>
#include <sstream>
#include <vector>
#include <QFileDialog>
#include <QMessageBox>
#include<QString>
#include<QDebug>
using namespace std;


namespace Ui {
class Show_Detail;
}

class Show_Detail : public QDialog
{
    Q_OBJECT

public:
    string tempstr;
    set<string> coauthor_tree;
    long long div_finder;
    explicit Show_Detail(QWidget *parent = nullptr);
    ~Show_Detail();

    void show_Publication(string search_name);
    void Generate_PublicationList (vector<string> Publicationinfo,vector<string> Publicationnode);

private slots:


    void on_showdetail_clicked();

private:
    Ui::Show_Detail *ui;
};

#endif // SHOW_DETAIL_H
