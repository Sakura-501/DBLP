#ifndef BEAUTIFULQSS_H
#define BEAUTIFULQSS_H

#include<QFile>
#include<QApplication>
//重载qss,用于美化界面
class BeautifulQss
{
public:
    static void setStyle(const QString &style) {
        QFile qss(style);
        qss.open(QFile::ReadOnly);
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
};


#endif // BEAUTIFULQSS_H
