#include "AdjacentTableGraph.h"//需要在文件中加该文件的函数声明，此文件大量错误
template <class T>
void ATGraph<T>::DFSArtiual(int index){
	//从index个顶点出发深度优先遍历图，找到关键结点
	int min,w;
	ArcNode *p;
	visited[index] = min = ++count;//index是第count个访问的结点位置
	for(p = atgraph.vertexs[index].firstarc;p;p = p->nextarc){
		//检查位置为index的顶点的每一个邻接顶点
		w = p->adjvex;//w存放位置为index的顶点的邻接顶点位置
		if (visited[w] == false) {
			DFSArtiual(w);//返回前求low[w]
			if(low[w] < min) {
				min = low[w];
			}
			if(low[w] >= visited[index])
				cout << index <<" "<<atgraph.vertexs[index].data<<endl;//输出关键结点
		} else if(visited[w] < min){//w已经访问，w是v0在生成树上的祖先
			min = visited[w];
		}
	}
	low[index] = min;
}
template <class T>
void ATGraph<T>::FindArcticul(){
	//查找并输出Ｇ上的全部关结点
	int i,index;
	ArcNode *p;
	count = 1;
	low[0] = visited[0] = 1;//将位置为0的顶点设置为生成树的根
	for(i = 1;i < atgraph.vexNum;++i){
		//初始化尚未访问顶点的访问数组
		visited[i] = 0;
	}
	p = atgraph.vertexs[0].firstarc;
	index = p->adjvex;
	DFSArtiual(index);//从第index个顶点出发深度优先查找关结点
	if(count < atgraph.vexNum){
		cout << "0 "<<atgraph.vertexs[0].data<<endl;//根是关结点
		while(p->nextarc){
			p = p->nextarc;
			index = p->adjvex;
			if(visited[index] == 0)
				DFSArtiual(index);
		}//endwhile
	}
}
