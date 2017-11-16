//前缀表达式（波兰式）即表达式的最前端（左）式运算符操作数在后
//操作过程：从右向左遍历表达式遇见数字则进栈，遇见操作符则将栈顶的两个运算数出栈进行运算（单目操作符取一个数）

// 将中缀表达式转换为前缀表达式：
// 遵循以下步骤：
// (1) 初始化两个栈：运算符栈S1和储存中间结果的栈S2；
// (2) 从右至左扫描中缀表达式；
// (3) 遇到操作数时，将其压入S2；
// (4) 遇到运算符时，比较其与S1栈顶运算符的优先级：
// 	(4-1) 如果S1为空，或栈顶运算符为右括号“)”，则直接将此运算符入栈；
// 	(4-2) 否则，若优先级比栈顶运算符的*较高或相等*，也将运算符压入S1；
// 	(4-3) 否则，将S1栈顶的运算符弹出并压入到S2中，再次转到(4-1)与S1中新的栈顶运算符相比较；
// (5) 遇到括号时：
// 	(5-1) 如果是右括号“)”，则直接压入S1；
// 	(5-2) 如果是左括号“(”，则依次弹出S1栈顶的运算符，并压入S2，直到遇到右括号为止，***此时将这一对括号丢弃***；
// (6) 重复步骤(2)至(5)，直到表达式的最左边；
// (7) 将S1中剩余的运算符依次弹出并压入S2；
// (8) 依次弹出S2中的元素并输出***从右向左写即先出栈的写在最右边***，结果即为中缀表达式对应的前缀表达式

//后缀表达式
//从左至右扫描表达式，遇到数字时，将数字压入堆栈，遇到运算符时，弹出栈顶的两个数，
//用运算符对它们做相应的计算（次顶元素 op 栈顶元素），并将结果入栈；
//重复上述过程直到表达式最右端，最后运算得出的值即为表达式的结果。

// 将中缀表达式转换为后缀表达式：
// 与转换为前缀表达式相似，遵循以下步骤：
// (1) 初始化两个栈：运算符栈S1和储存中间结果的栈S2；
// (2) 从左至右扫描中缀表达式；
// (3) 遇到操作数时，将其压入S2；
// 	(4) 遇到运算符时，比较其与S1栈顶运算符的优先级：
// 	(4-1) 如果S1为空，或栈顶运算符为左括号“(”，则直接将此运算符入栈；
// 	(4-2) 否则，若优先级比栈顶运算符的*高*(相等时也压入s2)，也将运算符压入S1（注意转换为前缀表达式时是优先级较高或相同，而这里则不包括相同的情况）；
// 	(4-3) 否则，将S1栈顶的运算符弹出并压入到S2中，再次转到(4-1)与S1中新的栈顶运算符相比较；
// (5) 遇到括号时：
// 	(5-1) 如果是左括号“(”，则直接压入S1；
// 	(5-2) 如果是右括号“)”，则依次弹出S1栈顶的运算符，并压入S2，直到遇到左括号为止，此时将这一对括号丢弃；
// (6) 重复步骤(2)至(5)，直到表达式的最右边；
// (7) 将S1中剩余的运算符依次弹出并压入S2；
// (8) 依次弹出S2中的元素并输出，结果的逆序即为中缀表达式对应的后缀表达式（转换为前缀表达式时不用逆序）。

#include <iostream>
#include "process.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
#include "SqStack.h"
char pause;
char Precede(char t1,char t2) {//运算符比较优先级
	//比较过程按照从左到右的顺序遍历表达式，判断运算符优先级
	char f;
	switch(t2){
		case '+':
		case '-':
			if (t1=='('||t1=='=') {
				f = '<';
			} else {
				f = '>';//返回t1的大小
			}
			break;
		case '*':
		case '/':
			if (t1=='*'||t1=='/'||t1==')') {
				f='>';
			} else {
				f='<';
			}
			break;
		case '(':
			if (t1==')') {
				cout<<"ERROR1"<<endl;
				exit(0);
			} else {
				f='<';
			}
			break;
		case ')':
			switch(t1){
				case '(':
					f ='=';
					break;
				case '=':
					cout<<"ERROR2"<<endl;
					exit(0);
				default:f='>';
			}
			break;
		case '=':
			switch(t1){
				case '=':
					f='=';
					break;
				case '(':
					cout<<"ERROR2"<<endl;
					exit(0);
				default: f='>';
			}
	}
	return f;
}
int In(char c) {//判断c是否为运算符
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '=':
		case '(':
		case ')':return 1;
		default:return 0;
	}
}
float Operate(float a,char theta,float b) {//进行一次运算
	float c;
	switch(theta) {
		case '+':
			c=a+b;
			break;
		case '-':
			c=a-b;
			break;
		case '*':
			c=a*b;
			break;
		case '/':
			c=a/b;
	}
	return c;
}
float Val_Exp(char *exp) {//由中缀表达式求值；op为运算符栈，od为运算数栈
	//优先级高的可以直接入栈，* / ">" + - ">" ) 遇到左括号则将有括号之前的出栈且括号抵消
	SqStack<char> OP(20);
	SqStack<float> OD(20);
	char theta;
	float a,b,d;
	char c,x;//存放键盘接受的字符
	char z[6];//存放浮点数字符串
	int i;
	OP.Push('=');//=是表达式结束表示
	c=*exp++;
	x=OP.GetTop();
	while(c!='='||x!='=') {
		if(In(c)){
			switch(Precede(x,c)){
				case '<':
					OP.Push(c);//栈顶优先级低
					c=*exp++;
					break;
				case '=':
					x=OP.Pop();//脱括号并接受下一个字符
					c=*exp++;
					break;
				case '>':
					theta=OP.Pop();//退栈，将结果入栈
					b=OD.Pop();
					a=OD.Pop();
					OD.Push(Operate(a,theta,b));
				} 
			}else if(c>='0'&&c<='9'||c=='.') {
				i=0;
				do{
					z[i]=c;
					i++;
					c=*exp++;
				}while(c>='0'&&c<='9'||c=='.');
				z[i]='\0';
				d=atof(z);//将字符串转化为字符型存于d
				OD.Push(d);
			} else {
				cout<<"ERROR3"<<endl;//c是非法字符
				exit(0);
			}
			x=OP.GetTop();
		}
		d=OD.GetTop();
		return d;//d 是运算结果
	}
void CreatePostExp(char *exp,char *postexp) {//由中缀求后缀
	char c,x;
	int i=0;
	SqStack<char> OP(20);
	OP.Push('=');
	cout<<"exp:"<<exp<<endl;
	c=*exp++;
	while(c){
		if ((c>='0'&&c<='9')||c=='.') {
			postexp[i++]=c;
			c=*exp++;
		}
		if (In(c)) {
			postexp[i++]=' ';
			x=OP.GetTop();
			switch(Precede(x,c)){
				case '<':
					OP.Push(c);
					c=*exp++;
					break;
				case '=':
					x=OP.Pop();
					c=*exp++;
					break;
				case '>':
					postexp[i++]=OP.Pop();//运算符出栈输出
					break;
			}
		}
		postexp[i]='\0';
	}
	cout<<"后缀表达式为："<<postexp<<endl;
}
float Val_PostExp(char * postexp) {//后缀表达式求值
	int i;
	char z[6];
	float v=0,d=0,a,b;
	char c;
	SqStack<float>OD(20);
	c=*postexp++;
	while(c!='\0'){
		if (c>='0'&&c<='9'||c=='.'){
			i=0;
			do{
				z[i++]=c;
				c=*postexp++;
			}while(c>='0'&&c<='9'||c=='.');
			z[i]='\0';
			d=atof(z);
			OD.Push(d);
		}
		if(In(c)){
			b=OD.Pop();
			a=OD.Pop();
			OD.Push(Operate(a,c,b));
			c=*postexp++;
		}
		c=*postexp++;
	}
	v=OD.Pop();
	return v;
}
int main(int argc, char const *argv[])
{
	char exp[20]="(2.2+5)+4*(5-3.1)=";
	char *postexp;
	postexp=new char[20];
	*postexp='\0';
	float v1;
	system("cls");
	int choice;
	do{
		cout<<"1--创建表达式\n";
		cout<<"2--表达式求值\n";
		cout<<"3--求后缀表达式\n";
		cout<<"4--后缀表达式求值\n";
		cout<<"5--显示表达式\n";
		cout<<"6--退出\n";
		cout<<"Enter choice:";
		cin>>choice;
		switch(choice){
			case 1://创建表达式
				cout<<"请输入以“=”结束的表达式："<<endl;//此时会覆盖初始化的表达式
				cin>>exp;
				cin.get(pause);
				system("pause");
				break;
			case 2://表达式求值
				v1=Val_Exp(exp);
				cout<<exp;
				cout<<v1<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 3://求后缀表达式
				CreatePostExp(exp,postexp);
				cin.get(pause);
				system("pause");
				break;
			case 4://后缀表达式求值
				v1=Val_PostExp(postexp);
				cout<<postexp<<"="<<v1<<endl;
				cin.get(pause);
				system("pause");
				break;
			case 5://显示表达式
				cout<<endl;
				cout<<"已创建的表达式为：";
				cout<<exp<<endl;
				if(strlen(postexp)){
					cout<<"后缀表达式为：";
					cout<<postexp<<endl;
				}
				cin.get(pause);
				system("pause");
				break;
			case 6://退出
				break;
			default:
			cout<<"Invalid choice"<<endl;
			break;
		}		
	}while(choice!=6);
	return 0;
}
