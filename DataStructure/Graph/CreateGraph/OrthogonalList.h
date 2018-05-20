#ifndef __ORLINKGRAPH__
#define __ORLINKGRAPH__

#include "../../Queue/LinkQueue.h"

#define MAX_VERTEX_NUM 20	
#define MAX_INFO 10		//informtion size

//Directed Graph
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
template <class T>
void OLGraph<T>::InsertVex(T v){
	olgraph.xlist[olgraph.vecNum].data = v;
	olgraph.xlist[olgraph.vecNum].firstin = olgraph.xlist[olgraph.vecNum];
	olgraph.xlist[olgraph.vecNum].firstout = NULL;
	olgraph.vecNum++;
}
template <class T>
bool OLGraph<T>::DeleteVex(T v){
	if(LocateVex(v) < 0)
		return false;
	ArcBox *p,*q;
	int k = LocateVex(v);
	if(k < 0)
		return false;
	for(int i = 0;i < olgraph.vecNum; ++i){
		if(i == k)
			continue;
		p = olgraph.xlist[i].firstin;
		while(p){
			if (p->tailVex == k && p == olgraph.xlist[i].firstin) {
				olgraph.xlist[i].firstin = p->hlink;
			} else if(p->tailVex != k){
				q = p;
				p = p->hlink;
			} else {
				q->hlink = p->hlink;
				break;
			}
		}//endwhile
	}//endfor
	p = olgraph.xlist[k].firstout;
	while(p){
		q = p->tlink;
		if(p->info)
			delete p->info;
		delete p;
		olgraph.arcNum--;
		p = q;
	}//endwhile
	for(int i = 0;i < olgraph.vecNum; ++i){
		if(i == k)
			continue;
		p = olgraph.xlist[i].firstout;
		while(p){
			if (p->headVex == k && p == olgraph.xlist[i].firstout) {
				olgraph.xlist[i].firstout = p->tlink;
				break;
			} else if(p->headVex != k){
				q = p;
				p = p->tlink;
			} else {
				q->tlink = p->tlink;
				break;
			}
		}
	}//endfor
	p = olgraph.xlist[k].firstin;
	while(p){
		q = p->hlink;
		if(p->info)
			delete p->info;
		delete p;
		olgraph.arcNum--;
		p = q;
	}//endwhile
	for(int i = k+1;i < olgraph.vecNum; ++i){
		olgraph.xlist[i-1] = olgraph.xlist[i];
	}//endfor
	olgraph.vecNum--;
	for(int i = 0;i < olgraph.vecNum; ++i){
		p = olgraph.xlist[i].firstout;
		while(p){
			if(p->tailVex > k)
				p->tailVex--;
			if(p->headVex > k)
				p->headVex--;
			p = p->tlink;
		}//endwhile
	}//endfor
	return true;
}
template <class T>
bool OLGraph<T>::InsertArc(T v,T w){
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i < 0||j < 0)
		return false;
	ArcBox *p = new ArcBox;
	p->tailVex = i;
	p->headVex = j;
	p->hlink = olgraph.xlist[j].firstin;
	p->tlink = olgraph.xlist[i].firstout;
	olgraph.xlist[j].firstin = olgraph.xlist[i].firstout = p;
	olgraph.arcNum++;
	p->info = NULL;
	return true;
}
template <class T>
bool OLGraph<T>::DeleteArc(T v,T w){
	ArcBox *p1,*p2;
	int i = LocateVex(v);
	int j = LocateVex(w);
	if(i < 0||i == j)
		return false;
	p2 = olgraph.xlist[i].firstout;
	if(p2 && p2->headVex == j)
		olgraph.xlist[i].firstout = p2->tlink;
	else {
		while(p2 && p2->headVex != j){
			p1 = p2;
			p2 = p2->tlink;
		}//endwhile
		if(p2)
			p1->tlink = p2->tlink;
	}
	p2 = olgraph.xlist[j].firstin;
	if(p2 && p2->tailVex == i)
		olgraph.xlist[j].firstin = p2->hlink;
	else {
		while(p2 && p2->tailVex != i){
			p1 = p2;
			p2 = p2->hlink;
		}
		if(p2)
			p1->hlink = p2->hlink;
	}
	if(p2->info)
		delete p2->info;
	delete p2;
	olgraph.arcNum--;
	return true;
}
template <class T>
void OLGraph<T>::Display(){
	ArcBox *p;
	cout << "Vertexs " << olgraph.vecNum << "Arcs " << olgraph.arcNum << endl;
	for(int i = 0;i < olgraph.vecNum; ++i){
		cout << "Vertex "<< olgraph.xlist[i].data <<":In_Arc:";
		p = olgraph.xlist[i].firstin;
		while(p){
			cout << olgraph.xlist[p->tailVex].data << " ";
			p = p->hlink;
		}
		cout << "Out_Arc:";
		p = olgraph.xlist[i].firstout;
		while(p){
			cout << olgraph.xlist[p->headVex].data << " ";
			p = p->tlink;
		}
		p = olgraph.xlist[i].firstout;
		while(p){
			if(p->info)
				cout << "Arc infomation: "<<p->info<<" ";
			p = p->tlink;
		}
		cout << endl;
	}//endfor
}
template <class T>
void OLGraph<T>::DFS(int index){
	ArcBox *p;
	visited[index] = true;
	if(!VisitFunc(olgraph.xlist[index].data))
		return;
	p = olgraph.xlist[index].firstout;
	while(p && visited[p->headVex])
		p = p->tlink;
	if(p && !visited[p->headVex])
		DFS(p->headVex);
}
template <class T>
bool OLGraph<T>::DFSTraverse(bool (*visit)(T v)){
	VisitFunc = visit;
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < olgraph.vecNum; ++i){
		if(!visited[i])
			DFS(i);
	}//endfor
	cout << endl;
	return true;
}
template <class T>
bool OLGraph<T>::BFSTraverse(bool (*visit)(T v)){
	LinkQueue<int> q;
	int receive;
	T u1;
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < olgraph.vecNum; ++i){
		if(!visited[i]){
			visited[i] = true;
			if(!visit(olgraph.xlist[i].data))
				return false;
			q.EnQueue(i);
			while(!q.QueueEmpty()){
				receive = q.DeQueue();
				u1 = GetVex(receive);
				for(int j = FirstAdjVex(u1); j >= 0;j = NextAdjVex(u1,GetVex(j))){
					if(!visited[j]){
						visited[j] = true;
						if(!visit(olgraph.xlist[j].data))
							return false;
						q.EnQueue(j);
					}
				}
			}//endwhile
		}
	}//endfor
	cout << endl;
	return true;
}
