#ifndef __HASHSEARCH__
#define __HASHSEARCH__

//T can only be assign as int,float,double,char
template <class T>
struct ElemType{
	T key;
	/* other data*/
};
template <class T>
class HashSearch{
	private:
		ElemType<T> *HT;	//stable address hashChart
		int count;			//the count of element
		int size;
	public:
		HashSearch();
		~HashSearch();
		void InitHashTable(int n);
		int Hash(T key);
		void Collision(int &s);		//conflict,find next adderss
		int Search(T key,int &s);	//hash search
		int Insert(ElemType<T> e);
		void Display();
};
#endif

template <class T>
HashSearch<T>::HashSearch(){
	HT = NULL;
	size = 0;
	count = 0;
}
template <class T>
HashSearch<T>::~HashSearch(){
	delete[] HT;
	count = 0;
}
template <class T>
void HashSearch<T>::InitHashTable(int n){
	cout<<"Please input default value of the same type to initialize keyword ";
	T def;
	cin >>def;
	size = n;
	HT = new ElemType<T>[size];
	for(int i = 0;i < size; ++i){
		HT[i].key = def;//key's type is T??????
	}//endfor
}
template <class T>
int HashSearch<T>::Hash(T key){
	int p = 5;
	return key % p;
}
template <class T>
void HashSearch<T>::Collision(int &s){
	s++;
}
template <class T>
int HashSearch<T>::Search(T key,int &s){
	s = Hash(key);
	while((HT[s].key != -1) && (key != HT[s].key)){
		Collision(s);
	}//endwhile
	if (HT[s].key == key) {
		return 1;
	} else {
		return 0;
	}
}
template <class T>
int HashSearch<T>::Insert(ElemType<T> e){//there is a bug
	int s;
	if (count == size) {
		cout<<"Table is full"<<endl;
		return -1;
	} else {
		s = Hash(e.key);
		int f = Search(e.key,s);
		if (f) {
			cout<<"elements exist!"<<endl;
			return -1;
		} else {
			HT[s].key = e.key;
			count++;
			return 1;
		}
	}
}
template <class T>
void HashSearch<T>::Display(){
	for(int i = 0;i < size; ++i){
		cout<<i<<'\t';
		if (HT[i].key != -1) {
			cout<<HT[i].key;
		} else {
			cout<<'\t';
		}
	}//endfor
	cout <<endl;
}
