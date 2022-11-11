#include "yearsanalysiswidget.h"
#include "ui_yearsanalysiswidget.h"

yearsAnalysisWidget::yearsAnalysisWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::yearsAnalysisWidget)
{
    ui->setupUi(this);
    for(int i=1936;i<=2022;i++){
        ui->Years->addItem(QString::asprintf("%d",i));
    }
    ui->Years->setCurrentText("Years");
    connect(ui->Years,&QComboBox::currentTextChanged,[=](){
        this->YearsText=ui->Years->currentText();
        YearsText="D:\\xmlhomework\\resource\\wordCould\\"+YearsText+"wordCloud.jpg";
        qDebug()<<YearsText;
        img=new QImage;
        img->load(YearsText);
        img->scaled(ui->showImageLabel->size(),Qt::KeepAspectRatio);
        ui->showImageLabel->setScaledContents(true);
        ui->showImageLabel->setPixmap(QPixmap::fromImage(*img));
    });
//    connect(ui->yearsABackButton,&QPushButton::clicked,[=](){
//        emit goBack();
//        qDebug()<<"a";
//    });
//    qDebug()<<YearsText;
//    ui->showImageLabel->setPixmap(QPixmap("://1936wordCloud.jpg"));
}

yearsAnalysisWidget::~yearsAnalysisWidget()
{
    delete ui;
}
