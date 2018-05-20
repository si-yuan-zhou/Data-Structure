#ifndef __ADJMULGRAP__
#define __ADJMULGRAP__

#include "../../Queue/LinkQueue.h"

#define MAX_VERTEX_NUM 20
#define MAX_INFO 10

//Undirected Graph
struct EBox{
	bool mark;			//flag of vertex whther be visited
	int ivex,jvex;		//position of the adjacent vertexs
	EBox *ilink,*jlink;	//point to the next adjacent edge
	char *info;			//infomation of the arc
};
template <class T>
struct VexBox{
	T data;			//vertex information
	EBox *firstedge;//point to the first edge adjacent this node
};
template <class T>
struct _AMGraph{
	VexBox<T> adjmullist[MAX_VERTEX_NUM];
	int vexnum,edgenum;
};
template <class T>
class AMGraph {
	_AMGraph<T> amgraph;
	bool visited[MAX_VERTEX_NUM];
	public:
		void CreateGraph();
		void DestroyGraph();
		int LocateVertex(T u);//return the position of node u
		T GetVertex(int idnex);//return value of the vertex at position index
		void PutVertex(T v,T value);//assign value to v
		int FirstAdjVertex(T v);//return the index of v's first adjacent vertrx
		int NextAdjVertex(T v,T w);//w is a adjacent vertex of v, and return the index of the next adjacent of v related to w, or return null if w is the last node of v
		void InsertVertex(T v);//add new vertex v
		bool DeleteVertex(T v);//delete vertex v and related arcs
		bool InsertArc(T v,T w);//add <v,w> and <w,v>
		bool DeleteArc(T v,T w);//delete <v,w> and <w,v>
		bool (*VisitFunc)(T v);//method of visiting vertexs
		void DFS(int index);//depth-first traversal start from index
		bool DFSTraverse(bool (*visit)(T v));
		bool BFSTraverse(bool (*visit)(T v));
		void MarkUnVisited();//set mark of edge as unvisited
		void Display();
};
#endif
template <class T>
int AMGraph<T>::LocateVertex(T v){
	for(int i = 0;i < amgraph.vexnum; ++i){
		if(amgraph.adjmullist[i].data == v)
			return i;
	}//endfor
	return -1;
}
template <class T>
void AMGraph<T>::CreateGraph(){
	int i,j;
	T va,vb;
	EBox *p;
	cout << "Please enter number of the vertexs and arcs of Undirected:";
	cin >>amgraph.vexnum >> amgraph.edgenum;
	cout << "Please enter vertexs value" << endl;
	for(i = 0;i < amgraph.vexnum;++i){
		cin >> amgraph.adjmullist[i].data;
		amgraph.adjmullist[i].firstedge = NULL;
	}
	cout << "Please enter the two vertexs of each arc successively" << endl;
	for(int k = 0;k < amgraph.edgenum; ++k){
		cin >> va >> vb;
		i = LocateVertex(va);
		j = LocateVertex(vb);
		p = new EBox;
		p->mark = false;
		p->ivex = i;
		p->jvex = j;
		p->info = NULL;
		p->ilink = amgraph.adjmullist[i].firstedge;
		amgraph.adjmullist[i].firstedge = p;
		p->jlink = amgraph.adjmullist[j].firstedge;
		amgraph.adjmullist[j].firstedge = p;
		p->info = NULL;
	}//endfor
}
template <class T>
T AMGraph<T>::GetVertex(int index){
	if(index < 0 || index >= amgraph.vexnum)
		return 0;
	return amgraph.adjmullist[index].data;
}
template <class T>
void AMGraph<T>::PutVertex(T v,T value){
	int i = LocateVertex(v);
	if(i < 0)
		return;
	amgraph.adjmullist[i].data = value;
}
template <class T>
int AMGraph<T>::FirstAdjVertex(T v){
	int i = LocateVertex(v);
	if(i < 0)
		return -1;
	if(amgraph.adjmullist[i].firstedge){
		if (amgraph.adjmullist[i].firstedge->ivex == i) {
			return amgraph.adjmullist[i].firstedge->jvex;
		} else {
			return amgraph.adjmullist[i].firstedge->ivex;
		}
	} else {
		return -1;
	}
}
template <class T>
int AMGraph<T>::NextAdjVertex(T v,T w){
	EBox *p;
	int i = LocateVertex(v);
	int j = LocateVertex(w);
	if(i < 0||j < 0)
		return -1;
	p = amgraph.adjmullist[i].firstedge;
	while(p){
		if(p->ivex == i && p->jvex != j){
			//not adjacent node, has two direction to find adjacent node
			p = p->ilink;
		} else if(p->jvex == i && p->ivex != j){
			p = p->jlink;
		} else {
			break;
		}
	}
	if(p && p->ivex == i && p->jvex == j){
		p = p->ilink;
		if (p&&p->ivex == i) {
			return p->jvex;
		} else if(p && p->jvex == i){
			return p->ivex;
		}
	}
	if(p && p->ivex == j && p->jvex == i){
		p = p->jlink;
		if (p&&p->ivex == i) {
			return p->jvex;
		} else if(p && p->jvex == i){
			return p->ivex;
		}
	}
	return -1;
}
template <class T>
void AMGraph<T>::InsertVertex(T v){
	if(amgraph.vexnum >= MAX_VERTEX_NUM)
		return;
	if(LocateVertex(v) >= 0)
		return;
	amgraph.adjmullist[amgraph.vexnum].data = v;
	amgraph.adjmullist[amgraph.vexnum].firstedge = NULL;
	amgraph.vexnum++;
}
template <class T>
bool AMGraph<T>::DeleteArc(T v,T w){
	EBox *p,*q;
	int i = LocateVertex(v);
	int j = LocateVertex(w);
	if(i < 0||j < 0||i == j)
		return false;
	//以下使指向待删边的第一个指针绕过这条边
	p = amgraph.adjmullist[i].firstedge;
	//第一条边为待删边
	if (p && p->jvex == j) {
		amgraph.adjmullist[i].firstedge = p->ilink;
	} else if(p && p->ivex == j){
		amgraph.adjmullist[i].firstedge = p->jlink;
	} else {
	//第一条边不为待删边
		while(p){
			if (p->ivex == i && p->jvex != j) {
				q = p;
				p = p->ilink;
			} else if(p->jvex == i&&p->ivex != j){
				q = p;
				p = p->jlink;
			} else {
				break;
			}
		}//endwhile
		if(!p)
			return false;
		if (p->ivex == i&&p->jvex == j) {
			if (q->ivex == i) {
				q->ilink = p->ilink;
			} else {
				q->jlink = p->ilink;
			}
		} else if(p->ivex == j&&p->jvex == i){
			if (q->ivex == i) {
				q->ilink = p->jlink;
			} else {
				q->jlink = p->jlink;
			}
		}
	}
	//以下从另一顶点起删除待删除边
	p = amgraph.adjmullist[j].firstedge;
	if(p->jvex == i){
		amgraph.adjmullist[j].firstedge = p->ilink;
		if(p->info)
			delete p->info;
		delete p;
	} else if(p->ivex == i){
		amgraph.adjmullist[j].firstedge = p->jlink;
		if(p->info)
			delete p->info;
		delete p;
	} else {
		while(p){//find <v,w>
			if (p->ivex == j && p->jvex != i) {//不是待删边
				q = p;
				p = p->ilink;
			} else if(p->jvex == j && p->ivex != i){
				q = p;
				p = p->jlink;
			} else {
				break;
			}
		}//endwhile
		if(p->ivex == i && p->jvex == j){
			if (q->ivex == j) {
				q->ilink = p->jlink;
			} else {
				q->jlink = p->jlink;
			}
		} else if(p->ivex == j&&p->jvex == i){
			if (q->ivex == j) {
				q->ilink = p->ilink;
			} else {
				q->jlink = p->ilink;
			}
			if(p->info)
				delete p->info;
			delete p;
		}
	}
	amgraph.edgenum--;
	return true;
} 
template <class T>
bool AMGraph<T>::DeleteVertex(T v){
	T w;
	EBox *p;
	int i = LocateVertex(v);
	if(i < 0)
		return false;
	for(int j = 0;j < amgraph.vexnum; ++j){
		//删除存在的与顶点v相连的边
		if(j == i)
			continue;
		w = GetVertex(j);
		DeleteArc(v,w);
	}//endfor
	for(int j = i+1;j < amgraph.vexnum;++j)//排在顶点v后面的顶点的序号减
		amgraph.adjmullist[j-1] = amgraph.adjmullist[j];
	amgraph.vexnum--;
	for(int j = i; j < amgraph.vexnum;++j){
		p = amgraph.adjmullist[j].firstedge;
		while(p){
			if (p->ivex == j+1) {
				p->ivex--;
				p = p->ilink;
			} else {
				p->jvex--;
				p = p->jlink;
			}
		}//endwhile
	}
	return true;
}
template <class T>
void AMGraph<T>::DestroyGraph(){
	for(int i = amgraph.vexnum-1;i >= 0;--i)
		DeleteVertex(amgraph.adjmullist[i].data);
}
template <class T>
bool AMGraph<T>::InsertArc(T v,T w){
	int i = LocateVertex(v);
	int j = LocateVertex(w);
	if(i < 0||j < 0)
		return false;
	EBox *p = new EBox;
	p->mark = false;
	p->ivex = i;
	p->jvex = j;
	p->info = false;
	p->ilink = amgraph.adjmullist[i].firstedge;
	amgraph.adjmullist[i].firstedge = p;
	p->jlink = amgraph.adjmullist[j].firstedge;
	amgraph.adjmullist[j].firstedge = p;
	amgraph.edgenum++;
	return true;
}
template <class T>
void AMGraph<T>::DFS(int index){
	VisitFunc(amgraph.adjmullist[index].data);
	visited[index] = true;
	EBox *p = amgraph.adjmullist[index].firstedge;
	while(p){//找下一个按深度访问的顶点
		int j = (p->ivex == index) ? p->jvex : p->ivex;//未访问则对其递归深度访问
		if(!visited[j])
			DFS(j);
		p = (p->ivex == index) ? p->ilink : p->jlink;
	}
}
template <class T>
bool AMGraph<T>::DFSTraverse(bool (*visit)(T v)){
	VisitFunc = visit;
	for(int i = 0;i < amgraph.vexnum; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < amgraph.vexnum; ++i){
		if(!visited[i])
			DFS(i);
	}//endfor
	cout << endl;
	return true;
}
template <class T>
bool AMGraph<T>::BFSTraverse(bool (*visit)(T v)){
	int receive;
	T u;
	for(int i = 0;i < amgraph.vexnum; ++i){
		visited[i] = false;
	}//endfor
	LinkQueue<int> q;
	for(int i = 0;i < amgraph.vexnum; ++i){
		if(!visited[i]){
			visited[i] = true;
			visit(amgraph.adjmullist[i].data);
			q.EnQueue(i);
			while(!q.QueueEmpty()){
				receive = q.DeQueue();
				u = GetVertex(receive);
				for(int j = FirstAdjVertex(u);j >= 0;j = NextAdjVertex(u,GetVertex(j))){
					if(!visited[j]){
						visited[j] = true;
						visit(amgraph.adjmullist[j].data);
						q.EnQueue(j);
					}
				}//endfor
			}//endwhile
		}
	}//endfor
	cout << endl;
	return true;
}
template <class T>
void AMGraph<T>::MarkUnVisited(){
	EBox *p;
	for(int i = 0;i < amgraph.vexnum; ++i){
		p = amgraph.adjmullist[i].firstedge;
		while(p){
			p->mark = false;
			p = (p->ivex == i) ? p->ilink : p->jlink;
		}//endwhile
	}//endfor
}
template <class T>
void AMGraph<T>::Display(){
	EBox *p;
	MarkUnVisited();
	cout << amgraph.vexnum <<" Vertexs"<<endl;
	for(int i = 0;i < amgraph.vexnum; ++i){
		cout << amgraph.adjmullist[i].data<<" ";
	}//endfor
	cout << endl;
	cout << amgraph.edgenum <<" Arcs"<<endl;
	for(int i = 0;i < amgraph.vexnum; ++i){
		p = amgraph.adjmullist[i].firstedge;
		while(p){
			if (p->ivex == i) {
				if(p->mark == false){
					cout << amgraph.adjmullist[i].data << "<->" << amgraph.adjmullist[p->jvex].data<<" ";
					p->mark = 1;
					if(p->info)
						cout << "Information: "<< p->info<<" ";
					cout << endl;
				}
				p = p->ilink;
			} else {
				if(p->mark == false){
					cout << amgraph.adjmullist[p->ivex].data <<"-"<<amgraph.adjmullist[i].data<<" ";
					p->mark = true;
					if(p->info)
						cout << "Information: "<<p->info<<" ";
					cout << endl;
				}
				p = p->jlink;
			}
		}//endwhile
	}//endfor
}
