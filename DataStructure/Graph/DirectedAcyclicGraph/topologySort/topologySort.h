#ifndef __TOPOLOGYSORT__
#define __TOPOLOGYSORT__

#define MAX_VERTEXNUM 100
struct ArcNode{
	int adjVex;			//该弧所指的顶点的位置
	ArcNode *nextarc;	//指向下一条弧的指针
	int *info;			//该弧相关信息的指针
};
template <class T>
struct VNode{
	T data;				//顶点信息
	ArcNode *firstarc;	//指向第一条依附该顶点的指针
};
template <class T>
struct _ALGraph{
	VNode<T> vertexs[MAX_VERTEXNUM];
	int vexnum;
	int arcnum;
	int kind;
};
template <class T>
class ALGraph {
	_ALGraph<T> algraph;
	bool visited[MAX_VERTEXNUM];
	int vexEarly[MAX_VERTEXNUM];//各顶点最早发生时间
	public:
		void CreateGraph();
		int LocateVex(T u);//图中存在顶点u，则返回该顶点在图中的位置
		void DestroyGraph();
		void Display();
		void FindInDegree(int indegree[]);//求顶点的入度
		bool TopologicalSort();//若图无回路，则输出图的顶点的一个拓扑序列
		bool TopologicalOrder(SqStack<int> &T);//求各顶点事件的最早发生时间vexEarly
		bool CriticalPath();//输出图的各项关键活动
};
template <class T>
void ALGraph<T>::FindInDegree(int indegree[]){
	ArcNode *p;
	for(int i = 0;i < algraph.vexnum; ++i){
		indegree[i] = 0;
	}//endfor
	for(int i = 0;i < algraph.vexnum; ++i){
		p = algraph.vertexs[i].firstarc;
		while(p){
			indegree[p->adjVex]++;
			p = p->nextarc;
		}
	}//endfor
}
template <class T>
bool ALGraph<T>::TopologicalSort(){
	int k,count = 0;
	int indegree[MAX_VERTEXNUM];//入度数组,存放各顶点当前入度数
	SqStack<int> S;
	ArcNode *p;
	FindInDegree(indegree);
	for(int i = 0;i < algraph.vexnum; ++i){
		if(!indegree[i]){
			S.push(i);//将i进栈
		}
	}//endfor
	while(!S.IsEmpty()){
		//当零入度顶点栈不空
		S.pop(i);//出栈１个零入度顶点的序号，并将其赋值给i
		cout << algraph.vertexs[i].data << " ";//输出i号顶点
		++count;//已输出顶点数+1
		for(p = algraph.vertexs[i].firstarc;p;p = p->nextarc){
			//对第i号顶点的每个邻接顶点
			k = p->adjVex;
			if(!(--indegree[k])){
				//k的入度减一1，若减为0，则将k入栈S
				S.push(k);
			}
		}
	}//endwhile
	if(count < algraph.vexnum){
		//零入度顶点栈S已空，图G还有顶点未输出
		cout << "有回路"<<endl;
		return false;
	} else {
		cout << "是一个拓扑序列"<<endl;
		return true;
	}
}
#endif
