class StringMatching
{
private:
	char *str;//存储串
	int len;//串长
public:
	StringMatching(char s[]);
	~StringMatching(){delete[] str;}
	void InputStr();//键盘输入创建串
	void OutputStr(){cout<<str<<endl;}//串输出
	int strLength(){return len;}//返回串长
	int IndexBF(char T[],int pos);//BF算法
	void GetNext(char T[],int next[]);//求NEXT
	int IndexKMP(char T[],int next[],int pose);//KMP匹配	
};
StringMatching::StringMatching(char s[]){
	str=s;
	len=strlen(s);
}
void StringMatching::InputStr() {
	cout<<"Please input string:";
	cin>>str;
	len=strlen(str);
}
int StringMatching::IndexBF(char T[],int pos) {
	//T 为要匹配的串，pos为从此处开始
	int i=0,j=0;
	int tlen=strlen(T);
	int length=len-pos;
	if(tlen>length)
		return -1;
	while(i<tlen&&j<length){
		if(str[j]==T[i]){
			i++;j++;
		} else {
			j=j-i+1;
			i=0;
		}
	}
	if(i>=tlen)
		return (j-tlen+1);
	else
		return -1;
}
void StringMatching::GetNext(char T[],int next[]) {

//http://www.cnblogs.com/yahong/p/3420565.html
//移动位数 = 已匹配的字符数 - 对应的部分匹配值
//next[0]=-1是因为当第一个就不匹配时移动位数为1，已
// 匹配的字符数为0，则特征值应为-1
//next函数需要优化，因为第i个值不等是，其前面的值可能
	// 与其相等，即没必要在比较，需要多向后移动

//next[i]={
// 	-1,                                 i=0
// 	max{0<k<i&p(0...k-1)=p(i-k,...i-1)},如果k存在
// 	0，                                 否则
// }

	int i=0,k=-1;
	int tlen=strlen(T);//模式串的长度
	next[0]=-1;
	while(i<tlen){
		while(k>=0&&T[i]!=T[k])
			k=next[k];
		i++;
		k++;
		if(i==tlen) break;
		if(T[i]==T[k])//相等则优化
			next[i]=next[k];
		else
			next[i]=k;
	}
}
int StringMatching::IndexKMP(char T[],int next[],int pos) {
	int i=0,j=pos;
	int tlen=strlen(T);
	int strLen=len-pos;
	if(strLen<tlen)
		return(-1);
	while(i<tlen&&j<strLen){
		if(i==-1||str[j]==T[i]){
			i++;
			j++;
		} else {
			i=next[i];
		}
	}
	if(i>=tlen)
		return (j-tlen+1);
	else
		return -1;
}
