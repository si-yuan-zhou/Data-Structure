//广义表即为LS=(a,b,...,(c,d))
//LS非空时，第一个元素的表头(Head)，其余元素组成的表是表尾(Tail)
//此模板中有功能相同的函数是因为有一个要递归调用
template <class T>
struct GLNode {
	int tag;//标志区域，区分原子节点和表节点
	T data;
	struct atom	{
		GLNode *hp,*tp;//分别指向表头和表尾
	}ptr;//ptr是表节点的指针域
};

template <class T>
class GLists {
public:
	GLists(){ls = NULL;}//初始化为空的广义表
	GLists(string st);//根据st建立广义表的存储结构
	GLists(GLists ls1,GLists ls2);//用表头ls1和表尾ls2构造广义表
	~GLists(){delete[] ls;}
	int DepthGList();//求广义表的深度
	int Length();//求广义表的长度
	GLists<T>* Head();//求广义表的表头
	GLists<T>* Tail();//求表尾
	void Print();//显示表
private:
	GLNode<T> *ls;//指向广义表的头指针
	char stprt[50];//显示些操作信息
	int chnumber;

	GLNode<T>* Crtlists(string st);//将st转化为广义表的头尾存储结构
	void Server(string &st,string &hst);//从st中取出第一成员存入hst，其余的成员留在st中
	void Ena(char ch);//存储广义表的输出信息
	int  Depth(GLNode<T> *ls);//求广义表的深度
	//void SetInfo();//初始化广义表的信息
	void Prt(GLNode<T> *ls);//将ls所指的广义表显示出来
};

template<class T>
GLists<T>::GLists(string st){
	ls = Crtlists(st);
}
template <class T>
GLists<T>::GLists(GLists ls1,GLists ls2) {
	//用两个广义表对象创建一个更大的广义表
	//用表头ls1与表尾ls2构造广义表
	GLNode<T> *p,*q,*ls;
	ls = new GLNode<T>;//建立广义表的头指针
	p  = new GLNode<T>;
	q  = new GLNode<T>;
	ls->tag = 1;//设置此节点为子表
	*p = *ls1.ls;
	*q = *ls2.ls;
	ls->ptr.hp = p;//把头指针指向ls1
	ls->ptr.tp = q;//把尾指针指向ls2
}
template<class T>
GLNode<T>* GLists<T>::Crtlists(string st){
	//bug:该函数对输入的st不做正确性检测，
	GLNode<T> *ls,*p,*q;
	string sub,hsub;
	if(st == "()")
		ls = NULL;
	else
		if(st.length() == 1) {
			//当广义表为单元素时，生成一个元素节点，填入值，并把节点赋给ls
			ls = new GLNode<T>;
			ls->tag = 0;
			ls->data = st[0];
		} else {
			ls = new GLNode<T>;
			ls->tag = 1;
			p = ls;
			sub = st.substr(1,st.length()-2);//去掉字符串两头的“（）”
			do {
				Server(sub,hsub);//从st中截取第一成员
				p->ptr.hp = Crtlists(hsub);//hsub可能是单元素节点子链表，用该函数找到子表的首节点
				q = p;
				if(sub != "") {
					p = new GLNode<T>;
					p->tag = 1;
					q->ptr.tp = p;
				}
			}while(sub != "");//此处的循环是继续创建子表的子表直到字符串遍历结束，每次保存的只是一个单节点值
			q->ptr.tp = NULL;//所有元素遍历完毕，在最后一个节点的尾指针指向NULL表示整个广义表结束
		}
	return ls;
}
template <class T>
int GLists<T>::DepthGList(){
	//之所以创建Depth和DepthGList两个函数是因为Depth要递归调用需传参
	return Depth(ls);
}
template <class T>
int GLists<T>::Depth(GLNode<T> *ls){
	//求广义表的深度，找括号的嵌套深度
	if(ls == NULL) return 1;//空表深度为1
	if(ls->tag == 0) return 0;//单元素深度为0
	int max = 0,dep;
	GLNode<T> *p = ls;
	while(p){
		dep = Depth(p->ptr.hp);//求以ptr.hp为头指针的子表即标的深度
		if(dep > max) max = dep;
		p = p->ptr.tp;
	}
	return max+1;//非空表的深度是各元素的深度的最大值加1（还有最外层的深度1）
}
template <class T>
int GLists<T>::Length(){
	//求表的长度，找逗号的个数加1
	if(ls == NULL) return 0;//空表长度为0
	int max = 1;
	GLNode<T> *p = ls->ptr.tp;
	while(p){
		max++;
		p = p->ptr.tp;
	}
	return max;
}
template <class T>
GLists<T>* GLists<T>::Head(){
	//求表头，之所以返回GLissts类型是因为显示函数是显示列表
	GLists<T> *hlists = new GLists<T>;//生成一个新的广义表
	if(ls->tag == 1)//如果ls有表头，则赋值给hlists
		hlists->ls = ls->ptr.hp;
	return hlists;
}
template <class T>
GLists<T>* GLists<T>::Tail(){
	//求表尾
	GLists<T> *tlists = new GLists<T>;
	if(ls->tag == 1)//如果ls有表尾，则赋值给tlists
		tlists->ls = ls->ptr.tp;
	return tlists;
}
template <class T>
void GLists<T>::Server(string &st,string &hst){
	//从st中取出第一成员存入到hst，其余的成员留在st中
	char ch;
	string sch;
	int i = 1,k = 0,n;
	n = st.length();
	do{
		sch = st.substr(i-1,1);//get one element each loop
		ch = sch[0];//it must get first element of sch because sch is string and ch is char
		switch(ch){
			case '(':
				k++;break;
			case ')':
				k--;break;
		}
		i++;
	/*
		对于while条件，跳出循环的条件有两种，
		1.找到头节点，即ch == ',' && k == 0(此处的st已经去掉了字符串最外侧的两个括号)
		2.全部遍历st 即i > n
	*/
	}while(!((i > n)||((ch == ',')&&(k == 0))));
	if(i <= n){
		//找到头节点
		hst = st.substr(0,i-2);//hst包含从st头开始到找到的逗号的前一个位置即为什么减2（去掉逗号和do外层的i++）
		st = st.substr(i-1,n-i+1);//st为剩余的字符
	} else {
		//st被遍历完，此种情况为长度为1的原子广义表
		hst = st;//全部给头节点
		st = "";
	}
}
template <class T>
void GLists<T>::Prt(GLNode<T> *ls) {
	//将ls所指的表显示出来
	GLNode<T> *p;
	if(ls != NULL){
		//如果ls为空则退出
		if(ls->tag == 1){
			//判断节点是不是表节点
			Ena('(');//先输出“（”

			Prt(ls->ptr.hp)//不断递归，直到输出子表的第一个元素
			p = ls->ptr.tp;//p指向子表的剩余部分
			
			while(p != NULL){
				Ena(',');//成员间加逗号

				Prt(p->ptr.hp);
				p = p->ptr.tp;
			}
			Ena(')');
		} else
			Ena(ls->data);//ls指向元素节点时输出元素节点的值
	}
}
template <class T>
void GLists<T>::Ena(char ch) {
	//存储要输出的信息
	stprt[chnumber] = ch;
	chnumber++;
}
// template <class T>
// void GLists<T>::SetInfo() {
// 	chnumber = 0;
// }
template <class T>
void GLists<T>::Print(){
	//显示出来
	//SetInfo();
	chnumber = 0;
	Prt(ls);
	for (int i = 0; i < chnumber; ++i)
		cout << stprt[i];
	cout << endl;
}
