#ifndef __StringMatch_H__
#define __StringMatch_H__

class StringMatching {
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
#endif

StringMatching::StringMatching(char s[]){
	str=s;
	len=strlen(s);
}
void StringMatching::InputStr() {
	cout<<"Please input Main String:";
	cin>>str;
	len=strlen(str);
}
int StringMatching::IndexBF(char T[],int pos) 
{
	//T 为要匹配的串，pos为从此处开始
	int i = 0, j = pos -1;
	int tlen = strlen(T);
	int length = len-pos+1;
	if (tlen > length)
		return -1;
	while (i < tlen && j < length) {
		if(str[j]==T[i]){
			i++;
			j++;
		} else {
			j=j-i+1;//i is the number which has been matched,
			//so,if the substring is not match,j should go back i steps,and move to the next postion
			i=0;
		}
	}
	if(i>=tlen)
		return (j-tlen+1);//add 1 since the index start from 0;
	else
		return -1;
}
void StringMatching::GetNext(char T[],int next[]) {
// next数组的含义就是一个固定字符串的最长前缀和最长后缀相同的长度
// next[j] store that how many steps j should move after mismatching.
/*http://www.cnblogs.com/yahong/p/3420565.html
移动位数 = 已匹配的字符数 - 对应的部分匹配值
next[0]=-1是因为当第一个就不匹配时移动位数为1 = 失配位置0 - 对应特征值k（-1），*/

	int i=0,k=-1;
	int tlen=strlen(T);//模式串的长度
	next[0]=-1;
	while(i < tlen){
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
	/*
		(not optimize)
		this step means that the first element matched,k increases and it will match the next element
		if not, k will be assgined next[0]--get back to the start place.
	while(i < tlen - 1) {
		if(k == -1 || T[i] == T[k]) {
			++k;
			++i;
			next[i] = k;
		} else
			k = next[k];
	}*/
}
int StringMatching::IndexKMP(char T[],int next[],int pos) {
	/*
		In KMP algorithm, if the element in mainstring is matched with the element in substring,
		the indexs i and j should both increse,yet,if not,the index of substring should be next[j],and
		the mianstring's should drive back j times and plus one since j elements in mainstring has
		been matched and need not match again.
	*/
	int i=0,j=pos;
	int tlen=strlen(T);
	int strLen=len-pos;
	GetNext(T,next);
	if(strLen<tlen)
		return -1;

	while(i < tlen && j < strLen){
		if(i == -1 || str[j] == T[i]){
			i++;
			j++;
		} else {
			i = next[i];
		}
	}

	if(i>=tlen)
		return j-tlen+1;
	else
		return -1;
}
