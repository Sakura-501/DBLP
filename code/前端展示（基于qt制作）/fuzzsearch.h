#ifndef FUZZSEARCH_H
#define FUZZSEARCH_H

#include <QDialog>
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
class FuzzSearch;
}

class FuzzSearch : public QDialog
{
    Q_OBJECT

public:
    explicit FuzzSearch(QWidget *parent = nullptr);
    ~FuzzSearch();

    void searchresult(string searchname);
    string inttostring(int i);

private slots:
    void on_search_clicked();

    void on_more_clicked();

    void on_exit_clicked();

private:
    Ui::FuzzSearch *ui;
};

#endif // FUZZSEARCH_H
