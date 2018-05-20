#ifndef __ARRAYGRAPH__
#define __ARRAYGRAPH__

#include <cstring>
#include <iomanip>
#include "../../Queue/LinkQueue.h"

#define MAX_VERTEX_NUM 20	//count of vertex(顶点)
const int infinity = 100;

struct ArcCell{
	int adj;		//for unweight graph, 1,0 indicates whether they are adjacent(相邻),
					//and for weight graphs they are weight-value
	char *info;		//arc(弧) information
};

template <class T>
struct _MGraph{
	T vertexs[MAX_VERTEX_NUM];						//vertex vector
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];	//adjacent martix
	int vertexNum;		//number of vertexs
	int arcNum;			//number of arcs
	int kind;			//storage type
};

template <class T>
class MGraph{
	private:
		_MGraph<T> mgraph;
		bool visited[MAX_VERTEX_NUM];

	public:
		void CreateGraph();			//create graph
		void DestroyGraph();		//destroy graph
		int  LocateVertex(T u);		//if there is a vertex u in the graph, the postion of the vertex in the graph should be returned
		T    GetVertex(int index);	//return the vertex value whose index number is index
		void PutVertex(T v,T value);//v is a vertex in graph, assign value to v
		int  FirstAdjVertex(T v);	//v is a vertex in graph,return the index of the first adjacent node of v,or null if there is no adjacent node
		int  NextAdjVertex(T v,T w);//v is a vertex,w is adjacent node of v,return the index of the next 
									//adjacent node of v relative to w,or null if w is the last adjacent node of v
		bool InsertVertex(T v);		//add a new vertex in graph
		bool DeleteVertex(T v);		//delete vertex v and it's associated arcs
		bool InsertArc(T v,T w);	//v and w are two arcs in graph,add arc <v,w> to graph or add symmetrical arc <w,v> as well 
									//if graph is undirected graph
		bool DeleteArc(T v,T w);	//contrary to insert operation
		bool CreateDG();			//create directed graph
		bool CreateDN();			//create directed net
		bool CreateUDG();			//create undirected graph
		bool CreateUDN();			//create undirected net
		void DFS(int index);		//traverse depth-first graph recursively from number index
		void Display();				//display adjacent martix
		bool (*VisitFunc)(T v);		//method of visiting vertexs
		bool DFSTraverse(bool (*visit)(T v));//depth-first
		bool BFSTraverse(bool (*visit)(T v));//breadth-first
};
#endif

template <class T>
bool visit(T v){
	//change the status of v as visited
	cout<<v<<" ";
	return true;
}
template <class T>
void MGraph<T>::CreateGraph(){
	cout<<"Please choose the category:\n"
		<<"0\tDirected Graph\n"
		<<"1\tDirected Net\n"
		<<"2\tUndirected Graph\n"
		<<"3\tUndirected Net: [ ]\b\b";
	cin>>mgraph.kind;
	switch(mgraph.kind){
		case 0:
			CreateDG();
			break;
		case 1:
			CreateDN();
			break;
		case 2:
			CreateUDG();
			break;
		case 3:
			CreateUDN();
			break;
		default:
			cout<<"no matched type"<<endl;
			//MGraph();
			break;
	}//endswitch
}
template <class T>
void MGraph<T>::DestroyGraph(){
	if(mgraph.kind < 2){//directed
		for(int i = 0;i < mgraph.vertexNum; ++i){
			for(int j = 0;j < mgraph.vertexNum; ++j){
				if(mgraph.arcs[i][j].info){
					delete[] mgraph.arcs[i][j].info;
					mgraph.arcs[i][j].info = NULL;
				}//endif
			}//endfor
		}//endfor
	} else {
		for(int i = 0;i < mgraph.vertexNum; ++i){
			for(int j = 0;j < mgraph.vertexNum; ++j){
				if(mgraph.arcs[i][j].info) {
					delete[] mgraph.arcs[i][j].info;
					mgraph.arcs[i][j].info = mgraph.arcs[j][i].info = NULL;
				}//endif
			}//endfor
		}//endfor
	}
	mgraph.vertexNum = 0;
	mgraph.arcNum = 0;
}
template <typename T>
T MGraph<T>::GetVertex(int index){
	//get the value of index vertex
	if (index < 0 || index >= mgraph.vertexNum){
		return 0;//transboundary return null
	}
	return mgraph.vertexs[index];
}
template <typename T>
void MGraph<T>::PutVertex(T v,T value){
	//change the value of v to value(parameter)
	int index = LocateVertex(v);
	if(index < 0)
		return;
	mgraph.vertexs[index] = value;
}
template <typename T>
bool MGraph<T>::CreateDG(){
	//create directed graph
	T v1,v2;
	cout <<"Please input the count of vertexs and arcs: ";
	cin  >>mgraph.vertexNum >>mgraph.arcNum;

	cout <<"Please enter each vertex:"<<endl;
	for (int i = 0; i < mgraph.vertexNum; ++i){
		cin >>mgraph.vertexs[i];
	}

	//initialise the whole matrix as 0
	for (int i = 0; i < mgraph.vertexNum; ++i){
		for (int j = 0; j < mgraph.vertexNum; ++j){
			mgraph.arcs[i][j].adj = 0;
			mgraph.arcs[i][j].info = NULL;
		}
	}
	for (int i = 0; i < mgraph.arcNum; ++i){
		//construct an adjacency matrix
		cout << "Please enter the start and end of an arc:";
		cin >>v1>>v2;
		int m = LocateVertex(v1);
		int n = LocateVertex(v2);
		mgraph.arcs[m][n].adj = 1;
	}
	mgraph.kind = 0;
	return true;
}
template <typename T>
bool MGraph<T>::CreateDN(){
	//construct directed network
	int w;
	T v1,v2;
	cout <<"Please enter the number of vertexs and arcs of directed network:";
	cin >>mgraph.vertexNum>>mgraph.arcNum;
	cout <<"Please enter each vertex: ";
	for (int i = 0; i < mgraph.vertexNum; ++i){
		cin >> mgraph.vertexs[i];//construct vertex vector
	}
	for (int i = 0; i < mgraph.vertexNum; ++i){//initialize adjacency matrix
		for (int j = 0; j < mgraph.vertexNum; ++j){
			mgraph.arcs[i][j].adj = infinity;
			mgraph.arcs[i][j].info = NULL;
		}
	}
	for (int i = 0; i < mgraph.arcNum; ++i){//construct adjacency matrix
		cout <<"Please enter the start, end, weight of arc: ";
		cin >> v1>>v2>>w;
		int m = LocateVertex(v1);
		int n = LocateVertex(v2);
		mgraph.arcs[m][n].adj = w;
	}
	mgraph.kind = 1;
	return true;
}
template <class T>
bool MGraph<T>::CreateUDG(){
	//construct undirected graph
	T v1,v2;
	cout << "Please enter number of vertexs and arxs of Undirected graph:";
	cin  >> mgraph.vertexNum >> mgraph.arcNum;
	cout << "Please enter each vertexs:";
	for(int i = 0;i < mgraph.vertexNum; ++i){
		//construct vertexs vector
		cin >> mgraph.vertexs[i];
	}//endfor
	for(int i = 0;i < mgraph.vertexNum; ++i){
		for(int j = 0;j < mgraph.vertexNum; ++j){
			mgraph.arcs[i][j].adj = 0;
			mgraph.arcs[i][j].info = NULL;
		}//endfor
	}//endfor
	for(int i = 0;i < mgraph.arcNum; ++i){
		//construct adjacent matrix
		cout << "Please enter two vertexs of a edge:";
		cin >> v1 >> v2;
		int m = LocateVertex(v1);
		int n = LocateVertex(v2);
		mgraph.arcs[m][n].adj = 1;	//<v1,v2>
		mgraph.arcs[n][m].adj = 1;	//<v2,v1>
	}//endfor
	mgraph.kind = 2;
	return true;
}
template <class T>
bool MGraph<T>::CreateUDN(){
	//construct undirected network
	int w;
	T v1,v2;
	cout << "Please enter vertexs and arcs of Undirected network:";
	cin >> mgraph.vertexNum >>mgraph.arcNum;
	cout << "Please enter each vertexs:";
	for(int i = 0;i < mgraph.vertexNum; ++i){
		cin >> mgraph.vertexs[i];
	}//endfor
	for(int i = 0;i < mgraph.vertexNum; ++i){
		for(int j = 0;j < mgraph.vertexNum; ++j){
			mgraph.arcs[i][j].adj = infinity;
			mgraph.arcs[i][j].info = NULL;
		}//endfor
	}//endfor
	for(int i = 0;i < mgraph.arcNum; ++i){
		//construct adjacent matrix
		cout << "Please two vertexs and weight of a edge:";
		cin >> v1 >> v2 >> w;
		int m = LocateVertex(v1);
		int n = LocateVertex(v2);
		mgraph.arcs[m][n].adj = w;
		mgraph.arcs[n][m].adj = w;
	}//endfor
	mgraph.kind = 3;
	return true;
}
template <class T>
int MGraph<T>::LocateVertex(T u){
	//return the index of vertex u in graph if it exist, otherwise -1 
	//index is the sub_index of storage vector
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		if(u == mgraph.vertexs[i]) {
			return i;
		}//endif
	}//endfor
	return -1;
}
template <class T>
int MGraph<T>::FirstAdjVertex(T v){
	//find first adjacent node the vertex v pointing to
	int temp = LocateVertex(v);
	int j = 0;
	if(mgraph.kind == 1||mgraph.kind == 3) {
		//if it's net
		j = infinity;
	}//endif
	for(int i = 0;i < mgraph.vertexNum; ++i){
		if(mgraph.arcs[temp][i].adj != j) {
			//when it unequal to j which means i is the first adjacent node
			return i;
		}//endif
	}//endfor
	return -1;//return null if no adjacent
}
template <class T>
int MGraph<T>::NextAdjVertex(T v,T w){
	//find the adjacent node of V counted after vertex W
	/*graph exists,V is a vertex in the graph, 
	  and W is the adjacency point of v,
	  return the next adjacent index of v relative to w.
	  if w is the last adjacent node of v,it return empty
	*/
	int id_v = LocateVertex(v);
	int id_w = LocateVertex(w);
	int j = 0;
	if(mgraph.kind == 1||mgraph.kind == 3) {
		j = infinity;
	}//endif
	for(int i = id_w+1;i < mgraph.vertexNum; ++i){
		if(mgraph.arcs[id_v][i].adj != j) {
			return i;
		}//endif
	}//endfor
	return -1;
}
template <class T>
bool MGraph<T>::InsertVertex(T v){
	//just add a vertex without any information with other arcs or vertexs
	if(mgraph.vertexNum >= MAX_VERTEX_NUM)
		return false;
	if(LocateVertex(v) >= 0)//the vertex has existed
		return false;

	mgraph.vertexs[mgraph.vertexNum] = v;//add v to the end of vertex vector
	for(int i = 0;i < mgraph.vertexNum; ++i){
		if (mgraph.kind % 2) {//net
			mgraph.arcs[mgraph.vertexNum][i].adj = infinity;
			mgraph.arcs[i][mgraph.vertexNum].adj = infinity;
		} else {//graph
			mgraph.arcs[mgraph.vertexNum][i].adj = 0;
			mgraph.arcs[i][mgraph.vertexNum].adj = 0;
		}
		mgraph.arcs[mgraph.vertexNum][i].info = NULL;
		mgraph.arcs[i][mgraph.vertexNum].info = NULL;
	}//endfor
	mgraph.vertexNum++;
	return true;
}
template <class T>
bool MGraph<T>::InsertArc(T v,T w){
	/*graph exists,v and w is two vertexs in graph,
	  add an arc <v,w> to a graph
	  a symmetry arc <w,v> should also be added if graph is undirected graph
	 */
	int v1,w1,weight;
	v1 = LocateVertex(v);
	w1 = LocateVertex(w);

	if(v1 < 0||w1 < 0) {
		return false;
	}//endif

	//these vertexs have existed and the operation just change the information between vertexs
	if (mgraph.kind % 2) {	//net
		cout << "Please enter the weight of this edge:";
		cin >>weight;
		mgraph.arcs[v1][w1].adj = weight;
	} else {				//graph
		mgraph.arcs[v1][w1].adj = 1;
	}
	if(mgraph.kind > 1) {	//undirected
		mgraph.arcs[w1][v1].adj = mgraph.arcs[v1][w1].adj;
		mgraph.arcs[w1][v1].info= mgraph.arcs[v1][w1].info; 
	}//endif
	mgraph.arcNum++;
	return true;
}
template <class T>
bool MGraph<T>::DeleteVertex(T v){
	//graph exists, delete vertex v and its related arcs
	int i,delpos,vrtype = 0;
	delpos = LocateVertex(v);

	if(delpos < 0)	//v don't exist
		return false;

	if(mgraph.kind % 2)//net
		vrtype = infinity;

	//delete the arc information pointing to delpos
	for(i = 0;i < mgraph.vertexNum; ++i){
		if(mgraph.arcs[i][delpos].adj != vrtype){
			//there are edges between v and other nodes
			if(mgraph.arcs[i][delpos].info){
				//delete the arc information related to v
				delete[] mgraph.arcs[i][delpos].info;
				mgraph.arcs[i][delpos].info = NULL;
				mgraph.arcs[delpos][i].info = NULL;
			}
			mgraph.arcNum--;
		}
	}//endfor
	if(mgraph.kind < 2){
		//directed
		//delete arc information delpos points to
		//frankly,the effect in this scrope is only for decreasing arcNum because information has been deleted in the last for-loop
		for(int j = 0;j < mgraph.vertexNum;++j){
			if(mgraph.arcs[delpos][j].adj != vrtype){
				//have out arc
				if(mgraph.arcs[delpos][j].info){
					delete[] mgraph.arcs[delpos][j].info;
					mgraph.arcs[delpos][i].info = NULL;
				}
				mgraph.arcNum--;
			}
		}
	}

	//delete vertex from storage vector
	for(int i = delpos+1; i < mgraph.vertexNum;++i){
		//the vertex vector after the serial number delpos move forward successively
		mgraph.vertexs[i-1] = mgraph.vertexs[i];
	}
	//delete the correspond colum from adjacent matrix
	for(int i = 0;i < mgraph.vertexNum; ++i){
		//moves the right matrix element of the deleted vertex
		for(int j = delpos+1;j < mgraph.vertexNum; ++j){
			mgraph.arcs[i][j-1] = mgraph.arcs[i][j];
		}//endfor
	}//endfor
	//delete the correspond row from adjacent matrix
	for(int i = delpos+1;i < mgraph.vertexNum; ++i){
		//moves the matrix element below the vertex delete
		for(int j = 0;j < mgraph.vertexNum; ++j){
			mgraph.arcs[j-1][i] = mgraph.arcs[j][i];
		}//endfor
	}//endfor
	mgraph.vertexNum--;
	return true;
}
template <class T>
bool MGraph<T>::DeleteArc(T v,T w){
	/*graph exists,v and w is two vertexs of graph,
	  delete arc <v,w> in graph
	  a symmetry arc <w,v> should also be deleted if it's undirected graph
	*/
	int v1,w1;
	v1 = LocateVertex(v);
	w1 = LocateVertex(w);

	if(v1 < 0||w1 < 0) {
		return false;
	}

	//delete arc information
	if(mgraph.kind % 2 == 0){//graph
		mgraph.arcs[v1][w1].adj = 0;
	} else {
		mgraph.arcs[v1][w1].adj = infinity;
	}
	if(mgraph.arcs[v1][w1].info){
		delete[] mgraph.arcs[v1][w1].info;
		mgraph.arcs[v1][w1].info = NULL;
	}

	if(mgraph.kind > 1){//undirected
		mgraph.arcs[w1][v1].adj = mgraph.arcs[v1][w1].adj;
		mgraph.arcs[w1][v1].info = NULL;
	}
	mgraph.arcNum--;
	return true;
}
template <class T>
void MGraph<T>::Display(){
	//display adjacency matrix
	char graphkind[20];
	char arckind[5];
	switch(mgraph.kind){
		case 0:
			strcpy(graphkind,"Directed_Graph");
			strcpy(arckind,"arc");
			break;
		case 1:
			strcpy(graphkind,"Directed_Net");
			strcpy(arckind,"arc");
			break;
		case 2:
			strcpy(graphkind,"UDirected_Graph");
			strcpy(arckind,"edge");
			break;
		case 3:
			strcpy(graphkind,"UDirected_Net");
			strcpy(arckind,"edge");
			break;
	}//endswitch
	cout << mgraph.vertexNum <<"vertex(s) "<< mgraph.arcNum <<" "<< arckind <<" of "<<graphkind<<endl;
	cout <<"Vertexs are: ";
	for(int i = 0;i < mgraph.vertexNum; ++i){
		cout << mgraph.vertexs[i] <<" ";
	}//endfor
	cout << "Adjacency matrix :" <<endl;
	for(int i = 0;i < mgraph.vertexNum; ++i){
		for(int j = 0;j < mgraph.vertexNum; ++j){
			if (mgraph.arcs[i][j].adj == infinity) {
				cout << setw(5) << "Inf" <<'\t';
			} else {
				cout << setw(5) << mgraph.arcs[i][j].adj <<'\t'; 
			}
		}//endfor
		cout << endl << endl;
	}//endfor
}
template <class T>
void MGraph<T>::DFS(int index){
	//recursively depth-first traversal from the index vertex

	visited[index] = true;	//has been visited
	VisitFunc(mgraph.vertexs[index]); //visit the index vertexs
	T v1 = GetVertex(index);
	for(int i = FirstAdjVertex(v1);i >= 0;i = NextAdjVertex(v1,GetVertex(i))){
		if(!visited[i])
			DFS(i);	//recursively calling DFS() on those adjacent nodes of v that has not been visited yet
	}
}
template <class T>
bool MGraph<T>::DFSTraverse(bool (*visit)(T w)){
	//depth-first traversal of a graph
	VisitFunc = visit;
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor
	for(int i = 0;i < mgraph.vertexNum; ++i){
		//depth-first traversal of each unvisited vertex
		if(!visited[i])
			DFS(i);
	}//endfor
	cout << endl;
	return true;
}
template <class T>
bool MGraph<T>::BFSTraverse(bool (*visit)(T v)){
	//breadth-first traversal
	LinkQueue<int>q;
	int receive;
	T u1;

	//initialize visited array
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		visited[i] = false;
	}//endfor

	for(int i = 0;i < mgraph.vertexNum;++i){
		//breadth-first traversal of each unvisited vertex
		if(!visited[i]){//not be visited

			if(!visit(mgraph.vertexs[i]))//访问出错
				return false;

			visited[i] = true;
			q.EnQueue(i);
			while(!q.QueueEmpty()){
				//the first element pop queue and set it as receive
				receive = q.DeQueue();
				u1 = GetVertex(receive);
				for(int j = FirstAdjVertex(u1);j >=0;j = NextAdjVertex(u1,GetVertex(j))){
					//FirstAdjVertex(u1) is the first adjacent of ui
					//NextAdjVertex is the next element related to FirstAdjVertex in the row ui
					//NextAdjVertex return -1 if there is no adjacent node

					//this for-loop is traverse the ui whole row
					if(!visited[j]){
						visited[j] = true;
						if(!visit(mgraph.vertexs[j]))
							return false;
						q.EnQueue(j);//push this row into queue
					}
				}//layer traverse over
			}//endwhile
		}
	}
	cout << endl;
	return true;
}
