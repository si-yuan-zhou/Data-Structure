#ifndef __STATICSEARCH__
#define __STATICSEARCH__

template <class T>
struct Node{
	T key;
	/*other data can be added*/
};

template <class T>
class StaticSearch {
	private:
		Node<T> *ST;	//chart first address
		int len;		//length of chart
		bool storted;
	public:
		StaticSearch();
		~StaticSearch();
		void Create(int n);
		void Display();
		int endSearch(T key);	//search from the last element
		void AscendSort();		//ascend sort
		int UR_BiSearch(T key);	//binary search un-recursively
		int R_BiSearch(T key);	//binary search recursively
		int R_BiSearch(int x,int y,T key);
};
#endif
template <class T>
StaticSearch<T>::StaticSearch(){
	ST = NULL;
	len = 0;
	storted = false;
}
template <class T>
StaticSearch<T>::~StaticSearch(){
	delete[] ST;
	len = 0;
}
template <class T>
void StaticSearch<T>::Create(int n){
	len = n;
	ST = new Node<T>[len];
	Node<T> e;
	int i = 0;

	cout<<"Please input "<<len<<" elements"<<endl;
	while(i < len){
		cin >> e.key;
		ST[i] = e;
		i++;
	}//endwhile
}
template <class T>
int StaticSearch<T>::endSearch(T key){
	//search key from the last one in StaticChart and return position otherwise return -1
	for(int i = len-1;i >= 0; --i){
		if(ST[i].key == key) {
			cout<<"Successfully! Element at "<<i+1<<endl;
			return i;
		}//endif
	}//endfor
	cout<<"NO ELEMENTS!"<<endl;
	return -1;
}
template <class T>
void StaticSearch<T>:: AscendSort(){
	//Sort the chart, all elements have been stored in array
	T t;
	for(int i = 0;i < len-1; ++i){
		for(int j = 0;j < len-i-1; ++j){
			if(ST[j].key > ST[j+1].key) {
				t = ST[j].key;
				ST[j].key = ST[j+1].key;
				ST[j+1].key = t;
			}//endif
		}//endfor
	}//endfor
	storted = true;
}
template <class T>
int StaticSearch<T>::UR_BiSearch(T key){
	if(len == 0 && ST == NULL && storted == false) {
		cout<<"The array has not been storted,Or NO StaticChart, Please create one first"<<endl;
		return -1;
	} else {
		int low = 0,high = len-1,mid;
		while(low <= high){
			mid = (low + high)/2;
			if(ST[mid].key == key) {
				cout<<"Get it at "<<mid+1<<endl;
				return mid;
			}//endif
			if (ST[mid].key > key) {
				high = mid - 1;
			} else {
				low = mid + 1;
			}
		}//endwhile
	}
	cout<<"No Element!"<<endl;
	return -1;
}
template <class T>
int StaticSearch<T>::R_BiSearch(int x,int y,T key){
	//x and y is the range, x(low) and y(high)
	int mid = (x+y)/2;
	if(ST[mid].key == key) {
		return mid;
	}//endif
	if(x>y) {
		return -1;
	}//endif
	if (key < ST[mid].key) {
		return R_BiSearch(x,mid-1,key);
	} else {
		return R_BiSearch(mid+1,y,key);
	}
}
template <class T>
int StaticSearch<T>::R_BiSearch(T key){
	int k = R_BiSearch(0,len-1,key);
	return k;
}
template <class T>
void StaticSearch<T>::Display(){
	cout<<"KeyWord in StaticChart:"<<endl;
	for(int i = 0;i < len; ++i){
		cout <<ST[i].key<<" ";
	}//endfor
	cout<<endl;
}
