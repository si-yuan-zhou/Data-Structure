const int defaultSize=128;
class AString {
private:
	char *ch;//存放串的数组
	int curLength;//串的实际长度
	int maxSize;//串数组最大长度
	void CheckMem();//检测内存是否申请成功
public:
	AString();
	AString(int sz);//构造最大长度为sz的字符长
	AString(const char *init);//最大长度为maxsize，由init初始化的字符串对象
	AString(const AString &ob);//由已有对象构造新的对象
	~AString(){delete[] ch;}
	AString& operator=(const char* str);
	//在成员函数的参数列表后使用const是表示此函数对数据成员只能进行读操作，不能更改数值

	//字符串对象的比较运算
	int operator==(AString &ob)const{return strcmp(ch,ob.ch)==0;}//判断当前实例是否与ob串相等，相等返回1，否则返回0
	int operator!=(AString &ob)const{return strcmp(ch,ob.ch)!=0;}
	int operator<(AString &ob)const{return strcmp(ch,ob.ch)<0;}
	int operator>(AString &ob)const{return strcmp(ch,ob.ch)>0;}
	int operator<=(AString &ob)const{return strcmp(ch,ob.ch)<=0;}
	int operator>=(AString &ob)const{return strcmp(ch,ob.ch)>=0;}

	//字符串的比较运算
	int operator==(char *str)const{return strcmp(ch,str)==0;}
	int operator<(char *str)const{return strcmp(ch,str)<0;}
	int operator>(char *str)const{return strcmp(ch,str)>0;}
	int operator<=(char *str)const{return strcmp(ch,str)<=0;}
	int operator>=(char *str)const{return strcmp(ch,str)>=0;}
	int operator!=(char *str)const{return strcmp(ch,str)!=0;}

	AString& operator=(AString &ob);
	AString& operator+=(AString &ob);
	AString& operator+=(const char* str);
	char& operator[](int i);//返回档当前串的第i个字符
	bool IsEmpty()const{return curLength==0;}
	int Length()const{return curLength;}
	void SubString(AString &subs,int index,int length);//从index开始截取length长的字符串并存放在subs中
	AString& Remove(int startIndex, int length);//从startIndex开始删除length个字符
	AString& Insert(int pos,const char * value);//在pos处插入value
	void Clear();
	void Output();
};

void AString::CheckMem() {
	if(ch==NULL){
		cerr<<"Memary distribute false!";
		exit(1);
	}
}
AString::AString(){
	maxSize=defaultSize;
	curLength=0;
	ch=new char[maxSize];
	CheckMem();
	ch[0]='\0';
}
AString::AString(int sz){
	maxSize=sz;
	curLength=0;
	ch=new char[maxSize+1];
	CheckMem();
	ch[0]='\0';
}
AString::AString(const char* init){
	int initLength=strlen(init);
	maxSize=(initLength>defaultSize)?initLength:defaultSize;
	ch=new char[maxSize+1];
	CheckMem();
	curLength=initLength;
	strcpy(ch,init);
}
AString::AString(const AString &ob) {
	maxSize=ob.maxSize;
	ch=new char[maxSize+1];
	CheckMem();
	strcpy(ch,ob.ch);
	curLength=ob.curLength;
}
AString& AString::operator=(AString &ob){
	if(&ob!=this){
		Clear();
		curLength=ob.curLength;
		strcpy(ch,ob.ch);
	} else {
		cout<<"String error!";
	}
	return *this;
}
AString& AString::operator=(const char* str) {
	int strLength=strlen(str);
	maxSize=strLength>maxSize?strLength:maxSize;
	Clear();
	strcpy(ch,str);
	curLength=strLength;
	return *this;
}
AString& AString::operator+=(AString &ob) {
	char *tempCH=ch;
	char *tempOb=ob.ch;
	int addLength=curLength+strlen(tempOb);
	maxSize=maxSize>addLength?maxSize:addLength;
	char *temp=new char[maxSize+1];
	char *tempT=temp;
	while(*tempCH!='\0')
		*tempT++=*tempCH++;
	while(*tempOb!='\0')
		*tempT++=*tempOb++;
	*tempT++='\0';
	Clear();
	strcpy(ch,temp);
	curLength=strlen(ch);
	delete[] temp;
	return *this;
}
AString& AString::operator+=(const char*str) {
	char *tempCH=ch;
	int addLength=curLength+strlen(str);
	maxSize=maxSize>addLength?maxSize:addLength;
	char *temp=new char[maxSize+1];
	char *tempT=temp;
	while(*tempCH!='\0')
		*tempT++=*tempCH++;
	while(*str!='\0')
		*tempT++=*str++;
	*tempT++='\0';
	Clear();
	strcpy(ch,temp);
	curLength=strlen(ch);
	delete[] temp;
	return *this;
}
char& AString::operator[](int i){
	if(i<0||i>curLength){
		cerr<<"String bottom bound";
		exit(1);
	}
	return ch[i];
}
void AString::SubString(AString &subs,int index,int length){
	if(index<0||index+length>maxSize||length<0){
		cerr<<"Error";
		exit(1);
	}
	if(IsEmpty()){
		cerr<<"String is Empty";
		exit(1);
	} else {
		char *temp=new char[length+1];
		if(temp==NULL){
			cerr<<"Memary error"<<endl;
			exit(1);
		}
		for (int i = 0,j=index; i < index; ++i,++j) {
			temp[i] = ch[j];
		}
		temp[length]='\0';
		subs=temp;
	}
}
AString& AString::Remove(int startIndex,int length) {
	if(startIndex<0||length<0||startIndex+length>maxSize){
		cerr<<"Retrival exceed bound";
		exit(1);
	}
	if(IsEmpty()) {
		cerr<<"String Empty",exit(1);
	}
	for (int i = 0; i < curLength-startIndex-length; ++i)
	//此处删除是用后面的覆盖掉前面的，若剩余部分（curLength-startIndex-length）
	//小于length,则会报错，应为越界，所以只能移动curLength-startIndex-length次，
	//在最后加上'\0'结束，使length-（curLength-startIndex-length）部分被覆盖
	{
		ch[i+startIndex]=ch[i+length+startIndex];
	}
	ch[curLength-length]='\0';
	curLength=strlen(ch);
	return *this;
}
AString& AString:: Insert(int pos ,const char *value) {
	if (pos>curLength||pos<0)
	{
		cerr<<"place error";
		exit(1);
	}
	int addLength=strlen(value)+curLength;
	maxSize=addLength>maxSize?addLength:maxSize;
	char *temp=new char[maxSize+1];
	char *tempCH=ch;
	char *tempH=temp;
	for (int i = 0; i < pos; ++i)
		*temp++=*tempCH++;//将插入点之前的放在临时串中
	while(*value!='\0')
		*temp++=*value++;//将要插入的串连接在临时串的尾部
	while(*tempH!='\0')
		*temp++=*tempCH++;//将原串的剩余部分加入临时串
	*temp='\0';
	Clear();
	strcpy(ch,tempH);
	curLength=strlen(ch);
	return *this;
}
void AString::Clear(){
	delete[] ch;
	ch=new char[maxSize+1];
	CheckMem();
	ch[0]='\0';
	curLength=0;
}
void AString::Output(){
	if(IsEmpty())
		cerr<<"String is Empty";
	else
		cout<<ch<<endl;
}
