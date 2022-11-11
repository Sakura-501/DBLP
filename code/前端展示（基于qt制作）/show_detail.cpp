#include "show_detail.h"
#include "ui_show_detail.h"

Show_Detail::Show_Detail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Show_Detail)
{
    ui->setupUi(this);

}

Show_Detail::~Show_Detail()
{
    delete ui;
}

static string DBLP_URL="D:\\xmlhomework\\resource\\src\\";
bool abandonflag;//禁止标志，防止字符串过少
int viewmore_activated;//更多浏览标记，记录流指针指向行数
bool showmore_signal;//更多浏览标志，让用户读取后面的搜索词条

long long stolongl(string str) //string转long long
{
    long long result;
    stringstream is(str);
    is >> result;
    return result;
}

void transformer_Filename(string &tmp_nickname)//nickname特殊字符变换
{if(tmp_nickname.length()<3){
         QMessageBox::information(NULL, Show_Detail::tr("Warning!"), Show_Detail::tr("An abortion has been activated.Please make sure you have entered 3 words at least!"));
        //QMessageBox::information(NULL, tr("Warning"), tr("An abortion has been activated!Please make sure you have entered 3 words at least."));
    abandonflag=1;
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

bool check_TailElem(string elemstr)//尾节点判定
{
    if ((elemstr.find("</article>") != string::npos) || (elemstr.find("</inproceedings>") != string::npos) ||
        (elemstr.find("</proceedings>") != string::npos) || (elemstr.find("</book>") != string::npos) ||
        (elemstr.find("</incollection>") != string::npos) || (elemstr.find("</phdthesis>") != string::npos) ||
        (elemstr.find("</mastersthesis>") != string::npos) || (elemstr.find("</www>") != string::npos))
        return true;
    else return false;
}

bool check_PrimaryElemName(string elemstr)//一级节点判定
{
    if ((elemstr.find("article") != string::npos) || (elemstr.find("inproceedings") != string::npos) ||
        (elemstr.find("proceedings") != string::npos) || (elemstr.find("book") != string::npos) ||
        (elemstr.find("incollection") != string::npos) || (elemstr.find("phdthesis") != string::npos) ||
        (elemstr.find("mastersthesis") != string::npos) || (elemstr.find("www") != string::npos))
        return true;
    else return false;
}


void Show_Detail::Generate_PublicationList
(vector<string> Publicationinfo,vector<string> Publicationnode)//生成Publication列表
{
    int actioncounter=0;
    vector <string>::iterator PLiter=Publicationinfo.begin();
     vector <string>::iterator PLnodeiter=Publicationnode.begin();
    while (PLiter != Publicationinfo.end())
    {
        QString qstr;
        QString nodestr;
        nodestr=QString::fromStdString(*PLnodeiter);
        qstr = QString::fromStdString(*PLiter);
        if(check_TailElem(nodestr.toStdString()))break;
        ui->listWidget->addItem(new QListWidgetItem(QIcon(":/images/info2"),nodestr));
        ui->listWidget->addItem(new QListWidgetItem("      "+qstr));
        ++PLiter;
        ++PLnodeiter;
       actioncounter++;
    }

     ui->ShowText->append("Total number:"+QString::number(actioncounter));
     ui->ShowText->append("Process finished!");
}

void Show_Detail::show_Publication(string search_name)//展示Publication主函数        //给一个文章名
{
    ui->ShowText->clear();
    long long div_finder=0;
    abandonflag=0;
    string tmp_nickname=search_name.substr(0,3);
    transformer_Filename(tmp_nickname);
    if(abandonflag==1){return;}
    //ifstream infile("G:\\dblp\\src\\publication\\" + tmp_nickname + ".txt", ios::in);
    ifstream infile(DBLP_URL+"publication\\" + tmp_nickname + ".txt", ios::in);

    getline(infile, tempstr);
    while (!infile.eof()) {
        if (tempstr.find(search_name) != string::npos)          //找到这篇文章 获取偏移量
        {
            size_t startPos = tempstr.find_last_of("=")+1;//urlpt="中，获取=的位置后+1，即“位置
            size_t endPos = tempstr.find_last_of("\"");//最后的”位置
            div_finder=stolongl(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
            break;
        }
        getline(infile, tempstr);
    }
    infile.close();
    if (div_finder != 0)
    {
        vector<string> Publicationnode;
        vector<string> Publicationinfo;
        //ifstream indblp("G:\\dblp\\src\\dblp.xml", ios::in| ios::binary);
        ifstream indblp(DBLP_URL+"dblp.xml", ios::in| ios::binary);

        indblp.seekg(div_finder,ios::beg);    //跳到偏移量的位置
        getline(indblp, tempstr);
        ui->ShowText->append( QString::fromStdString(tempstr));//article行   //此函数把string变成QString
        getline(indblp, tempstr);
        while (!check_TailElem(tempstr)) {//测试用
            ui->ShowText->append( QString::fromStdString(tempstr));      //用一个showText跑给人看
            size_t startPos2 = tempstr.find_first_of("<");
            size_t endPos2 = tempstr.find_first_of(">");
            string tmp2=tempstr.substr(startPos2 + 1, endPos2 - (startPos2+ 1));
            if(check_PrimaryElemName(tmp2))continue;
            Publicationnode.push_back(tmp2);              //存<author>里的antuor之类的提示信息

            size_t startPos = tempstr.find_first_of(">");
            size_t endPos = tempstr.find_last_of("<");
            string tmp=tempstr.substr(startPos + 1, endPos - (startPos + 1));
            Publicationinfo.push_back(tmp);               //内容
            getline(indblp, tempstr);

        }
        Generate_PublicationList(Publicationinfo,Publicationnode);
    }
}


void Show_Detail::on_showdetail_clicked()
{
    ui->ShowText->clear();
           ui->listWidget->clear();
           viewmore_activated=0;
           showmore_signal=0;
           QString TempInput=ui->inputName->text();
           this->show_Publication(TempInput.toStdString());   //标题名
}

