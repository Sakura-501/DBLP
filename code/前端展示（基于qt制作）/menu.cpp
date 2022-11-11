#include "menu.h"
#include "ui_menu.h"
#include"mainwindow.h"
#include"yearsanalysiswidget.h"
#include"author_works.h"
#include"show_coauthor.h"
#include"graph.h"
#include"cluster.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    //connect(&show_detail, SIGNAL(sdClose()), this, SLOT(ShowMainWnd()));

    ui->setupUi(this);
    this->setWindowTitle("菜单窗口");

    connect(ui->menuquit,&QPushButton::clicked,[=](){
        //点击退出按钮会弹出警告！
        if(QMessageBox::Yes == QMessageBox::question(this,"警告","确定退出系统？",
                                                     QMessageBox::Yes|QMessageBox::No))
        {
                this->close();

        }
    });
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_fuzz_clicked()
{
    //this->hide();
    //fs->show();
    FuzzSearch *fs=new FuzzSearch;
    fs->exec();
    //this->show();
}




void Menu::on_author_clicked()
{
    AuthorCount *ac=new AuthorCount;
    ac->exec();
}


void Menu::on_more_detail_clicked()
{
    Show_Detail *sd=new Show_Detail;
    sd->exec();
}


void Menu::on_Yearsanalyse_clicked()
{
    yearsAnalysisWidget* yearsAnalysis=new yearsAnalysisWidget();
    yearsAnalysis->show();
}


void Menu::on_author_work_clicked()
{
    Author_Works *aw=new Author_Works;
    aw->exec();
}


void Menu::on_show_coauthor_clicked()
{
   Show_Coauthor *sc=new Show_Coauthor;
   sc->exec();
}


void Menu::on_graph_clicked()
{
    Graph * g=new Graph();
    g->exec();
}


void Menu::on_cluster_analysis_clicked()
{
    Cluster * c = new Cluster();
    c->exec();
}

