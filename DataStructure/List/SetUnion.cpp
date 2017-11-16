#include <iostream>
#include "process.h"
using namespace std;
#include "LinkList.h"
typedef int T;
int main(int argc, char const *argv[])
{
	T e;
	LinkList<int> La,Lb;//represent Set A and Set B
	int la_len,lb_len;
	int i;
	cout<< "Please input the elements number of Set A:";
	cin>>la_len;
	cout<<endl;
	La.CreateList(la_len);
	cout<<"Please input the elemnets number of Set B:";
	cin>>lb_len;
	cout<<endl;
	Lb.CreateList(lb_len);
	cout<<"La:"<<endl;
	La.ListDisplay();
	cout<<endl;
	cout<<"Lb:"<<endl;
	Lb.ListDisplay();
	cout<<endl;
	for(i=1;i<=lb_len;i++) {
		try {
			e=Lb.GetElem(i);
		}
		catch(char *err) {
			cout<<err<<endl;
			cout<<"no"<<endl;
		}
		if(!La.Locate(e)) {
			try {
				La.Insert(++la_len,e);
			}
			catch (char *err) {
				cout<<err<<endl;
				cout<<"yes"<<endl;
			}
		}
	} 
	cout<<"union:"<<endl;
	La.ListDisplay();
	cout<<endl;
	return 0;
}
