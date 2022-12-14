#include "AllAuthorAnalysis_Writer.h"
#include <algorithm>
using namespace std;

string itostr(int temp)
{
	stringstream a;
	a << temp;
	string zz;
	a >> zz;
	return zz;
}

void AllAuthorWriter::Author_RBWriter()
{
	string tempstr;
	int counter = 0;//测试用
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);//文件读取,如果不是相对路径，请手动修改 
	getline(infile, tempstr);
	string tempauthor;
	int namecounter=1;//一开始姓名计数为1 
	while (tempstr.find("</dblp>") == string::npos) {
		if (tempstr.find("<author>") != string::npos)
		{
			size_t startPos = tempstr.find_first_of(">");
			size_t endPos = tempstr.find_last_of("<");
			tempauthor = tempstr.substr(startPos + 1, endPos - (startPos + 1));
			ofstream outfile(save_url +"allauthor\\namefile"+itostr(namecounter)+".aua", ios::app);//推测这里是 使用“namefile”+namecounter的文件名按顺讯一个个记录作者的名字 
			outfile << tempauthor << endl;
			counter++;//测试用
			if (counter % 1000 == 0)cout << "Author_RBWriter()::counter:" << counter << endl;
			if (counter % 100000 == 0)namecounter++;//当文本记录了10万个作者名字后换一个文本1记录。。。。。 
			outfile.close();
		}
		getline(infile, tempstr);		
	}
	cout << "Finished!" << endl;
}

//
//int main()
//{
//	save_url = "G:\\dblp\\src\\";
//	AllAuthorWriter a;
//	a.Author_RBWriter();
//}
