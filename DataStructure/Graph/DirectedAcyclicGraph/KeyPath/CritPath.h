#ifndef __CRITPATH__
#define __CRITPATH__

#include "../topologySort/topologySort.h"
#include "SqStack.h"

template <class T>
bool ALGraph<T>::TopologicalOrder(SqStack<int> &t){
	int k,count,indegree[MAX_VERTEXNUM];
	SqStack<int> s;
	ArcNode *p;
	FindInDegree(indegree);
	for(int i = 0;i < algraph.vexnum; ++i){
		if(!indegree[i]){
			s.push(i);
		}
	}//endfor
	count = 0;
	for(int i = 0;i < algraph.vexnum; ++i){
		vexEarly[i] = 0;
	}//endfor
	while(!s.IsEmpty()){
		s.pop(i);
		t.push(i);
		count++;//i号顶点如栈并计数
		for(p = algraph.vertexs[i].firstarc;p;p = p->nextarc){
			//对i号顶点的每个邻接点的入度减一
			k = p->adjVex;
			if(--indegree[k] == 0){
				//入度减为0,则入栈
				s.push(k);
			}
			if(vexEarly[i] + *(p->info)->vexEarly[k])
				vexEarly[k] = vexEarly[i] + *(p->info);
		}//endfor
	}
	if (count < algraph.vexnum) {
		cout << "有向图右回路"<<endl;
		return false;
	} else {
		return true;
	}
}
template <class T>
bool ALGraph<T>::CriticalPath(){
	int v1[MAX_VERTEXNUM];
	SqStack<int> t;
	int i,j,k,ee,el,dut;
	ArcNode *p;
	char tag;
	if(!TopologicalOrder(t))
		return false;
	j = vexEarly[0];
	for(i = 0;i < algraph.vexnum; ++i){
		//j 存储vexEarly最大值
		if(vexEarly[i] > j)
			j = vexEarly[i];
	}//endfor
	for(i = 0;i < algraph.vexnum; ++i){
		//初始化顶点时间最迟发生时间（最大值）
		//完成点的最早发生时间
		v1[i] = j;
	}//endfor
	while(!t.IsEmpty()){
		//按拓扑逆序求各顶点的v1值
		for(t.pop(j),p = algraph.vertexs[j].firstarc;p;p = p->nextarc){
			k = p->adjVex;
			dut = *(p->info);//dut<j,k>
			if(v1[k]-dut < v1[j])
				v1[j] = v1[k] - dut;
		}
	}//endwhile
	cout << "j  k  dut  ee  el  tag"<<endl;
	for(j = 0;j < algraph.vexnum;++j){
		//求ee,el和关键活动
		for(p = algraph.vertexs[j].firstarc;p;p=p->nextarc){
			k = p->adjVex;
			dut = *(p->info);
			ee = vexEarly[j];
			el = v1[k]-dut;
			tag = (ee==el)?'*':' ';
			cout << j << "  " << k << "  " << dut << "  "<< ee << "  " << el<<"  "<<tag<<endl;//输出关键活动
		}
	}
	cout << "关键活动为: "<<endl;
	for(j = 0;j < algraph.vexnum;++j){
		for(p = algraph.vertexs[j].firstarc;p;p=p->nextarc){
			k = p->adjVex;
			dut = *(p->info);
			if(vexEarly[j] == v1[k]-dut){
				cout << algraph.vertexs[j].data<<"->"<<algraph.vertexs[k].data<<endl;
			}
		}
	}
	return true;
}

#endif
