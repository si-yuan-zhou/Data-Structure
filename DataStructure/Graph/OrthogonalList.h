#ifndef __ORLINKGRAPH__
#define __ORLINKGRAPH__

#define MAX_VERTEX_NUM 20	
#define MAX_INFO 10		//informtion size

struct ArcBox{
	int tailVex,headVex;//tail and head position of this arc
	ArcBox *hlink,*tlink;//the link area of arc which has the same head and tail
	char *info;			//pointer related to this arc
};
template <class T>
struct VexNode{
	T data;
	ArcBox *firstin,*firstout;//point to the first inArc and outArc
};
template <class T>
struct _OLGraph{
	VexNode<T> xlist[MAX_VERTEX_NUM];//link head vector
	int vecNum,arcNum;	//Directed graph's vertexs and arcs
};
template <class T>
class OLGraph{
	_OLGraph<T> olgraph;
	bool visited[MAX_VERTEX_NUM];
	public:
	void CreateGraph();
	void DestroyGraph();
	int LocateVex(T u);//return position of u
	T GetVex(int index);//return value of index vertex
	void PutVex(T v,T value);//assgin value to v
	int FirstAdjVex(T v);//return the first adjcent node of v,otherwise null
	int NextAdjVex(T v,T w);//return the next adjacent node v related to w
	void InsertVex(T v);//add new vertex
	bool DeleteVex(T v);
	bool InsertArc(T v,T w);//add <v,w>
	bool DeleteArc(T v,T w);
	bool (*VisitFunc)(T v);
	void DFS(int index);
	bool DFSTraverse(bool (*visit)(T v));
	bool BFSTraverse(bool (*visit)(T v));
	void Display();
};
#endif
template <class T>
int OLGraph<T>::LocateVex(T u){
	for(int i = 0;i < olgraph.vecNum; ++i){
		if(olgraph.xlist[i].data == u)
			return i;
	}//endfor
	return -1;
}
template <class T>
void OLGraph<T>::CreateGraph(){
	int i,j,k;
	ArcBox *p;
	T v1,v2;
	cout << "Please enter number of vertex and arcs of Directed Graph:";
	cin >> olgraph.vecNum >> olgraph.arcNum;
	cout << "Please enter "<<olgraph.vecNum <<" Vertexs"<<endl;
	for(i = 0;i < olgraph.vecNum;++i){
		cin >> olgraph.xlist[i].data;
		olgraph.xlist[i].firstin = NULL;
		olgraph.xlist[i].firstout = NULL;
	}
	cout << "Please enter "<<olgraph.arcNum <<"arcs end and start"<<endl;
	for(k = 0;k < olgraph.arcNum;++k){
		cin >> v1 >> v2;
		i = LocateVex(v1);
		j = LocateVex(v2);
		p = new ArcBox;
		p->tailVex = i;
		p->headVex = j;
		p->hlink = olgraph.xlist[j].firstin;
		p->tlink = olgraph.xlist[i].firstout;
		olgraph.xlist[j].firstin = olgraph.xlist[i].firstout = p;
		p->info = NULL;
	}
}
template <class T>
void OLGraph<T>::DestroyGraph(){
	ArcBox *p,*q;
	for(int i = 0;i < olgraph.vecNum; ++i){
		p = olgraph.xlist[i].firstout;
		while(p){
			q = p;
			p = p->tlink;
			if(q->info)
				delete q->info;
			delete q;
		}
	}//endfor
	olgraph.arcNum = 0;
	olgraph.vecNum = 0;
}
template <class T>
T OLGraph<T>::GetVex(int index){
	if(index < 0||index >= olgraph.vecNum)
		return 0;//false
	return olgraph.xlist[index].data;
}
template <class T>
void OLGraph<T>::PutVex(T v,T value){
	int i = LocateVex(v);
	if(i < 0)
		return;
	olgraph.xlist[i].data = value;
}
template <class T>
int OLGraph<T>::FirstAdjVex(T v){
	int i = LocateVex(v);
	ArcBox *p = olgraph.xlist[i].firstout;
	if (p) {
		return p->headVex;
	} else {
		return -1;
	}
}
template <class T>
int OLGraph<T>::NextAdjVex(T v,T w){
	int i = LocateVex(v);
	int j = LocateVex(w);
	ArcBox *p = olgraph.xlist[i].firstout;
	while(p && p->headVex != j){
		p = p->tlink;
	}
	if(p)
		p = p->tlink;
	if(p)
		return p->headVex;
	else
		return -1;
}
