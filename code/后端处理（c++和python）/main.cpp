#include<iostream>
#include"misc.h"
#include<string>
#include"LinkedList.h"
using namespace std;
int main() {
	int n = 425957;
	int m = 1049866;
	string path1 = "D:\\paperana\\Project1\\src\\adList1.txt\0";
	char path[37] = {NULL};
	for (int i = 0; i < path1.size(); i++) {
		path[i]= path1[i];
	}
	LinkedList** link=readInGraphAdjListToDoubleEdges(&n, &m, path);
	
	runAndPrintStatsCliques(link, n);

}