#ifndef SHOW_COAUTHOR_H
#define SHOW_COAUTHOR_H

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
using namespace std;

namespace Ui {
class Show_Coauthor;
}

class Show_Coauthor : public QDialog
{
    Q_OBJECT

public:
    string tempstr;
    set<string> coauthor_tree;
    long long div_finder;

    explicit Show_Coauthor(QWidget *parent = nullptr);
    ~Show_Coauthor();

    void findAuthor_inDBLP();
    void show_Coauthor(string search_name);
    void probe_RBTree();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Show_Coauthor *ui;
};

#endif // SHOW_COAUTHOR_H
