#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    ui->setupUi(this);
//    for(int i=1936;i<=2022;i++){
//        ui->Years->addItem(QString::asprintf("%d",i));
//    }
    for(int i=1;i<=10;i++)
    {
        ui->Years->addItem(QString::asprintf("%d",i));
    }
    //ui->Years->addItem("author1");
    ui->Years->setCurrentText("authors");
    connect(ui->Years,&QComboBox::currentTextChanged,[=](){
        this->authortext=ui->Years->currentText();
        authortext="D:\\xmlhomework\\resource\\graph\\"+authortext+".png";
        qDebug()<<authortext;
        img=new QImage;
        img->load(authortext);
        img->scaled(ui->showImageLabel->size(),Qt::KeepAspectRatio);
        ui->showImageLabel->setScaledContents(true);
        ui->showImageLabel->setPixmap(QPixmap::fromImage(*img));
    });
}

Graph::~Graph()
{
    delete ui;
}
