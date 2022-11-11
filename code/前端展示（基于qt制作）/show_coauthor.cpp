#include "show_coauthor.h"
#include "ui_show_coauthor.h"
#include <fstream>
#include <string>
#include <set>

Show_Coauthor::Show_Coauthor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Coauthor)
{
    ui->setupUi(this);
}

Show_Coauthor::~Show_Coauthor()
{
    delete ui;
}


static string DBLP_URL="D:\\xmlhomework\\resource\\src\\";
bool abandonflag_2;//禁止标志，防止字符串过少
int viewmore_activated_2;//更多浏览标记，记录流指针指向行数
bool showmore_signal_2;//更多浏览标志，让用户读取后面的搜索词条

long long stolongl_2(string str) //string转long long
{
    long long result;
    stringstream is(str);
    is >> result;
    return result;
}

void transformer_Filename_2(string &tmp_nickname)//nickname特殊字符变换
{if(tmp_nickname.length()<3){
         QMessageBox::information(NULL, Show_Coauthor::tr("Warning!"), Show_Coauthor::tr("An abortion has been activated.Please make sure you have entered 3 words at least!"));
        //QMessageBox::information(NULL, tr("Warning"), tr("An abortion has been activated!Please make sure you have entered 3 words at least."));
    abandonflag_2=1;
    }
        if ((_stricmp(tmp_nickname.c_str(), "CON") == 0) || (_stricmp(tmp_nickname.c_str(), "PRN") == 0) ||
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

bool check_TailElem_2(string elemstr)//尾节点判定
{
    if ((elemstr.find("</article>") != string::npos) || (elemstr.find("</inproceedings>") != string::npos) ||
        (elemstr.find("</proceedings>") != string::npos) || (elemstr.find("</book>") != string::npos) ||
        (elemstr.find("</incollection>") != string::npos) || (elemstr.find("</phdthesis>") != string::npos) ||
        (elemstr.find("</mastersthesis>") != string::npos) || (elemstr.find("</www>") != string::npos))
        return true;
    else return false;
}

void Show_Coauthor::findAuthor_inDBLP()//在DBLP中检索作者
{

    if (div_finder != 0)
    {
        //ifstream indblp("G:\\dblp\\src\\dblp.xml", ios::in | ios::binary);
        ifstream indblp(DBLP_URL+"dblp.xml", ios::in | ios::binary);
        indblp.seekg(div_finder, ios::beg);
        while (!check_TailElem_2(tempstr)) {//测试用
            getline(indblp, tempstr);
            if (tempstr.find("<author>") != string::npos) {
                size_t startPos = tempstr.find_first_of(">");
                size_t endPos = tempstr.find_last_of("<");
                coauthor_tree.insert(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
            }
        }
    }
}

void Show_Coauthor::probe_RBTree()//遍历红黑树
{
        set<string>::iterator MJiter = coauthor_tree.begin();//迭代器，用于遍历整颗红黑树
        while (MJiter != coauthor_tree.end())
        {
            ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/people"),"author"));
            ui->listWidget->addItem(new QListWidgetItem("      "+QString::fromStdString(*MJiter)));
            ++MJiter;

        }
        if(showmore_signal_2==1)ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/more"),""));

}

void Show_Coauthor::show_Coauthor(string search_name)//展示所有合作作者
{
    div_finder = 0;
    abandonflag_2=0;
    string tmp_nickname = search_name.substr(0, 3);
    transformer_Filename_2(tmp_nickname);
    if(abandonflag_2==1){return;}


    //ifstream infile("G:\\dblp\\src\\coauthor\\" + tmp_nickname + ".txt", ios::in);
    ifstream infile(DBLP_URL+"coauthor\\" + tmp_nickname + ".txt", ios::in);
    if(!infile){
        QMessageBox::information(NULL, Show_Coauthor::tr("Warning!"), Show_Coauthor::tr("Cannot find such author."));
        return;
    }
    int counter=0;
    if(viewmore_activated_2>0){
        for(int i=0;i<viewmore_activated_2;i++)getline(infile, tempstr);
        coauthor_tree.clear();
    };
    getline(infile, tempstr);
    while (!infile.eof()) {
        if (tempstr.find(search_name) != string::npos)
        {
            size_t startPos = tempstr.find_last_of("=") + 1;//urlpt="中，获取=的位置后+1，即“位置
            size_t endPos = tempstr.find_last_of("\"");//最后的”位置
            div_finder = stolongl_2(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
           findAuthor_inDBLP();
           counter++;
           if(counter==50){viewmore_activated_2+=50;showmore_signal_2=1; break;}
        }
        getline(infile, tempstr);
    }
    infile.close();
    probe_RBTree();//遍历作者红黑树
}






void Show_Coauthor::on_pushButton_clicked()
{
    ui->ShowText->clear();
    ui->listWidget->clear();
    viewmore_activated_2=0;
    showmore_signal_2=0;
    QString TempInput=ui->inputName->text();
    this->show_Coauthor(TempInput.toStdString());
}

