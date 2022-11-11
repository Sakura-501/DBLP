#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include"fuzzsearch.h"
#include "authorcount.h"

#include"show_detail.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    //Show_detail show_detail;

    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_fuzz_clicked();

    void on_author_clicked();


    void on_more_detail_clicked();

    void on_Yearsanalyse_clicked();

    void on_author_work_clicked();

    void on_show_coauthor_clicked();

    void on_graph_clicked();

    void on_cluster_analysis_clicked();

private:
    Ui::Menu *ui;
    bool isUntitled;
        // 保存当前文件的路径
        QString curFile;
        QXmlStreamReader reader;
        int radioButton;
};

#endif // MENU_H
