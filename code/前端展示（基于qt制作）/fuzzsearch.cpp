#include "fuzzsearch.h"
#include "ui_fuzzsearch.h"

FuzzSearch::FuzzSearch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FuzzSearch)
{
    ui->setupUi(this);
    ui->resultlist->clear();
    //connect(ui->exit,SIGNAL(clicked()),this,SLOT(close()));


}

FuzzSearch::~FuzzSearch()
{
    delete ui;
}


bool abandonflag1;//禁止标志，防止字符串过少
int viewmore_activated1;//更多浏览标记，记录流指针指向行数
bool showmore_signal1;//更多浏览标志，让用户读取后面的搜索词条
int counter=0;
void FuzzSearch::on_search_clicked()
{

    //点击搜索后，首先清空
    ui->resultlist->clear();
    //将更多浏览标志置为0
    showmore_signal1=0;
    viewmore_activated1=0;
    counter=0;
    QString input=ui->fuzzinput->text();
    //ui->resultlist->addItem(input);
    this->searchresult(input.toStdString());

}


void FuzzSearch::searchresult(string searchname)
{
    //ui->resultlist->addItem(QString::fromStdString(searchname));
    //将更多浏览标志置为0
    showmore_signal1=0;
    string tempstr;
    for(int i=1;i<=88;i++)
        { //ifstream infile("G:\\dblp\\src\\year\\"+itostr(i)+".txt", ios::in| ios::binary);
          ifstream infile("D:\\xmlhomework\\xmlslover\\dblp\\dblp\\src\\TitlesSearch\\titlefile"+this->inttostring(i)+".txt", ios::in| ios::binary);
          //D:\xmlhomework\xmlslover\dblp\dblp\src\TitlesSearch
          while(!infile.eof()){
            getline(infile,tempstr);
            //ui->resultlist->addItem(QString::fromStdString(tempstr));
            //读进来之后，先把titlename截取出来比较
            size_t startposition=tempstr.find_first_of("\"");
            size_t endposition=tempstr.find_last_of("=");
            tempstr=tempstr.substr(startposition+1,endposition-(startposition+1)-10);
            //cout<<tempstr<<endl;
            if(tempstr.find(searchname)!=string::npos)
            {
                ui->resultlist->addItem(QString::fromStdString(tempstr));
                counter++;
            }

            //一次性展示十个，超过十个就暂停
            if(counter>10)
                {
                ui->more->setEnabled(true);
                QElapsedTimer t;
                t.start();
                while(t.elapsed()<1000000&&counter>=10)
                   QCoreApplication::processEvents();
            }


//            if(tempstr.find(ui->inputName->text().toStdString())!=string::npos)
//            {ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/info3"),QString::fromStdString(tempstr)));
//             counter++;
//             if(counter==50){viewmore_activated+=50;showmore_signal=1; break;}
//            }
//            if(showmore_signal==1)break;
                }
        }
        //if(showmore_signal==1){ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/more"),"[More Information]"));}

}

string FuzzSearch::inttostring(int i)
{
    stringstream s;
    s<<i;
    string result;
    s>>result;
    return result;
}


void FuzzSearch::on_more_clicked()
{
    ui->more->setEnabled(false);
    counter=0;
}


void FuzzSearch::on_exit_clicked()
{
    this->close();
}

