#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
#include<QStringList>
#include<QDebug>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<QStandardItem>
#include<iomanip>
#include<QDebug>
#include"menu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    Menu m;
};
#endif // MAINWINDOW_H
