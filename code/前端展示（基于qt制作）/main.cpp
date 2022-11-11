#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "beautifulqss.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //没大看懂，可能和我一开始创建项目选了中文有关
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qtxml_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//        db.setHostName("127.0.0.1");
//        db.setPort(3306);
//        db.setDatabaseName("数据库名");
//        db.setUserName("用户名");
//        db.setPassword("密码");
//        bool ok = db.open();
//        if (ok){
//            QMessageBox::information(this, "infor", "success");
//        }
//        else {
//            QMessageBox::information(this, "infor", "open failed");
//            qDebug()<<"error open database because"<<db.lastError().text();
//        }
//    qDebug()<<"available drivers:";
//        QStringList drivers = QSqlDatabase::drivers();
//        foreach(QString driver, drivers)
//            qDebug()<<driver;


    //这里真正开始。。
    BeautifulQss::setStyle(QDir::currentPath()+"/../qtxml/qtxml.qss");
    cout<<QDir::currentPath().toStdString();
    MainWindow w;
    w.show();
    return a.exec();
}
