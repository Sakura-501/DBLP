#include "author_works.h"
#include "ui_author_works.h"

Author_Works::Author_Works(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Author_Works)
{
    ui->setupUi(this);
}

Author_Works::~Author_Works()
{
    delete ui;
}


static string DBLP_URL="D:\\xmlhomework\\resource\\src\\";
bool abandonflag_1;//禁止标志，防止字符串过少
int viewmore_activated_1;//更多浏览标记，记录流指针指向行数
bool showmore_signal_1;//更多浏览标志，让用户读取后面的搜索词条

long long stolongl_1(string str) //string转long long
{
    long long result;
    stringstream is(str);
    is >> result;
    return result;
}

void transformer_Filename_1(string &tmp_nickname)//nickname特殊字符变换
{if(tmp_nickname.length()<3){
         QMessageBox::information(NULL, Author_Works::tr("Warning!"), Author_Works::tr("An abortion has been activated.Please make sure you have entered 3 words at least!"));
        //QMessageBox::information(NULL, tr("Warning"), tr("An abortion has been activated!Please make sure you have entered 3 words at least."));
    abandonflag_1=1;
    }
        if ((_stricmp(tmp_nickname.c_str(), "CON")== 0) || (_stricmp(tmp_nickname.c_str(), "PRN") == 0) ||
        (_stricmp(tmp_nickname.c_str(), "AUX") == 0) || (_stricmp(tmp_nickname.c_str(), "NUL") == 0))
        tmp_nickname += "_a";//特殊命名处理
    if (tmp_nickname.find(".") != string::npos)tmp_nickname.replace(tmp_nickname.find("."), 1, "_b");
    if (tmp_nickname.find("/") != string::npos)tmp_nickname.replace(tmp_nickname.find("/"), 1, "_c");
    if (tmp_nickname.find("\\") != string::npos)tmp_nickname.replace(tmp_nickname.find("\\"), 1, "_d");
    if (tmp_nickname.find("<") != string::npos)tmp_nickname.replace(tmp_nickname.find("<"), 1, "_e");
    if (tmp_nickname.find(">") != string::npos)tmp_nickname.replace(tmp_nickname.find(">"), 1, "_f");
    if (tmp_nickname.find("\"") != string::npos)tmp_nickname.replace(tmp_nickname.find("\""), 1, "_g");
    if (tmp_nickname.find(":") != string::npos)tmp_nickname.replace(tmp_nickname.find(":"), 1, "_h");
    if (tmp_nickname.find("|") != string::npos)tmp_nickname.replace(tmp_nickname.find("|"), 1, "_i");
    if (tmp_nickname.find("*") != string::npos)tmp_nickname.replace(tmp_nickname.find("*"), 1, "_j");
    if (tmp_nickname.find("?") != string::npos)tmp_nickname.replace(tmp_nickname.find("?"), 1, "_k");
    if (tmp_nickname.find(" ") != string::npos)tmp_nickname.replace(tmp_nickname.find(" "), 1, "_l");
    if (tmp_nickname.find("$") != string::npos)tmp_nickname.replace(tmp_nickname.find("$"), 1, "_m");
}

void Author_Works::show_works(string search_name)//展示作者所有文章信息 //输入作者名
{
    div_finder=0;
    abandonflag_1=0;
    string tmp_nickname = search_name.substr(0, 3);
    transformer_Filename_1(tmp_nickname);
    if(abandonflag_1==1){return;}
    //ifstream infile("G:\\dblp\\src\\coauthor\\" + tmp_nickname + ".txt", ios::in);
    ifstream infile(DBLP_URL+"coauthor\\" + tmp_nickname + ".txt", ios::in);
    if(!infile){
        QMessageBox::information(NULL, Author_Works::tr("Warning!"), Author_Works::tr("Cannot find such author."));
        return;
    }
    if(viewmore_activated_1>0){
        for(int i=0;i<viewmore_activated_1;i++)getline(infile, tempstr);
    };
    getline(infile, tempstr);
    int counter=0;
    while (!infile.eof()) {
        if (tempstr.find(search_name) != string::npos)
        {
            size_t startPos = tempstr.find_last_of("=") + 1;//urlpt="中，获取=的位置后+1，即“位置
            size_t endPos = tempstr.find_last_of("\"");//最后的”位置
            div_finder = stolongl_1(tempstr.substr(startPos + 1, endPos - (startPos + 1)));

            size_t pub_startPos = tempstr.find("pname=") + 6;
            size_t pub_endPos = tempstr.find("\" urlpt");
            string pub_name = tempstr.substr(pub_startPos + 1, pub_endPos - (pub_startPos + 1));
            ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/book"),"publication"));
            ui->listWidget->addItem(new QListWidgetItem("      "+QString::fromStdString(pub_name)));
            counter++;
            if(counter==50){viewmore_activated_1+=50;showmore_signal_1=1; break;}
        }
        getline(infile, tempstr);
    }
    if(showmore_signal_1==1)ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/more"),"[More Information]"));
    infile.close();
}

void Author_Works::on_pushButton_clicked()
{
    ui->ShowText->clear();
           ui->listWidget->clear();
           viewmore_activated_1=0;
           showmore_signal_1=0;
           QString TempInput=ui->inputName->text();
           this->show_works(TempInput.toStdString());
}

