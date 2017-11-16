//number system conversion
#include <iostream>
#include <stdio.h>
#include "process.h"
using namespace std; 
#include "SqStack.h"
template <class T>
void convert(T n,T m) {
	T e;
	char c;
	SqStack<int> s(10);//create a stack of length 10
	cout<<"The decimal need to convert:"<<n<<endl;
	while(n){
		try{
			s.Push(n%m);
		}
		catch(char *err){
			cout<<err<<endl;
		}
		n=n/m;
	}// n mod m continually before n equals zero
	cout<<"Convert to"<<m<<"number is:";
	while(!s.StackEmpty()) {
		try{
			e = s.Pop();
			if(e < 10)
				cout <<e<<'\t';
			else{//A means 10 and etc.
				c = 'A'+e-10;
				cout<<c<<'\t';
			}
		}
		catch(char *err){
			cout<<err<<endl;
		}
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	int n,m;
	char ans;
	int flag = 1;
	while(flag) {
		cout<<"Please enter the decimal number to convert:";
		cin>>n;
		cout<<"Please enter the number to be converted into the system:";
		cin>>m;
		convert(n,m);
		cout<<"Continue?Y/N";
		cin>>ans;
		if(ans == 'Y'||ans == 'y') {
			flag = 1;
		} else {
			flag = 0;
			cout <<"System drop out!"<<endl;
		}
	}//end while
	return 0;
}
