#include "TestingFramework.h"
using namespace std;

template <typename T>
struct Node{
	Node(T el, Node *n)
		:element(el)
		,next(n){
	}
	T element;
	Node *next;
};
template <typename T>
struct Head_Tail{
	Head_Tail(Node<T> *h,Node<T> *t)
		:head(h)
		,tail(t){
	}
	Node<T> *head;
	Node<T> *tail;
};

template <typename T>
class List{
public:
	List()
		:size_(0)
		,list_(NULL,NULL){
	}
	~List(){
		if(size_!=0){
			if(size_==1){
				delete list_.head;
			}else{
				while(list_.head!=list_.tail){
					delete list_.head;
					list_.head = list_.head->next;
				}
				delete list_.head;
			}
		}
	}
	bool chk_empty(){
		return (list_.head==NULL);
	}

	void push_back(T el){
		Node<T>* node=new Node<T>(el,NULL);
		if(chk_empty()){
			list_.head=node;
		}else{
			list_.tail->next=node;
		}
		list_.tail=node;
		++size_;
	}

	T operator [](int i){
		if(i>=size_){
			throw invalid_argument("argument>List_size");
		}
		Head_Tail<T> l=list_;
		int j=0;
		T el;
		while (j != i){
			delete l.head;
			l.head = l.head->next;
			++j;
		}
		el=l.head->element;
		while(l.head!=l.tail){
			delete l.head;
			l.head = l.head->next;
		}
		delete l.head;
		return el;
	}
	void pop_front(){
		if(!chk_empty()){
			delete list_.head;
			list_.head = list_.head->next;
			--size_;
		}
	}
	int size(){
		return size_;
	}
private:
	int size_;
	Head_Tail<T> list_;
};

void Test1(){
	List <int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	int sum = l[0]+l[1]+l[2]+l[3]+l[4];
	string s = to_string(sum)+to_string(l.size());
	AssertEqual(s,"155","Test1");
}
void Test2(){
	List <int> l;
	l.push_back(1);
	l.push_back(2);
	l.pop_front();
	string s = to_string(l[0])+to_string(l.size());
	AssertEqual(s,"21","Test2");
}
void Test3(){
	List <double> l;
	l.push_back(1.1);
	l.push_back(2.3);
	double sum = l[0]+l[1];
	string s = to_string(sum);
	AssertEqual(s,"3.400000","Test3");
}
void Test4(){
	List <string> l;
	l.push_back("qwe");
	l.push_back("rty");
	string s=l[0]+l[1];
	AssertEqual(s,"qwerty","Test4");
}
void Test5(){
	List <string> l;
	l.push_back("qwe");
	l.push_back("rty");
	l.pop_front();
	AssertEqual(l[0],"rty","Test5");
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(Test1,"Test1");
	tr.RunTest(Test2,"Test2");
	tr.RunTest(Test3,"Test3");
	tr.RunTest(Test4,"Test4");
	tr.RunTest(Test5,"Test5");
}

int main() {
	TestAll();
	List <string> l;
	l.push_back("qwe");
	l.push_back("rty");
	cout << "l[0]=" <<l[0] << endl
		 << "l[1]=" <<l[1] << endl
		 << "l.size()=" << l.size() << endl;
	l.pop_front();
	cout << "l[0]=" <<l[0] << endl
		 << "l.size()=" << l.size() << endl;
	return 0;
}
