#ifndef AUTHOR_WORKS_H
#define AUTHOR_WORKS_H

#include <QDialog>
#include <fstream>
#include <string>
#include <set>
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
using namespace std;

namespace Ui {
class Author_Works;
}

class Author_Works : public QDialog
{
    Q_OBJECT

public:
    string tempstr;
    set<string> coauthor_tree;
    long long div_finder;
    explicit Author_Works(QWidget *parent = nullptr);
    ~Author_Works();

    void show_works(string search_name);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Author_Works *ui;
};

#endif // AUTHOR_WORKS_H
