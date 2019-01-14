#include "TestingFramework.h"
using namespace std;

vector <string> Func(stringstream& ss,const char& c);
void Print(const vector <string>& V);
void Ignore(stringstream&ss,const char& c);

string Test(string S, const char& c){
	stringstream ss(S);
	vector <string> V = Func(ss,c);
	string s;
	for(const auto&v:V){
		s+=v;
		s.push_back('\n');
	}
	s.pop_back();
	return s;
}

void Test1(){
	string s=Test("qwe",'w');
	AssertEqual(s,"q\ne","Test1");
}
void Test2(){
	string s=Test("we",'w');
	AssertEqual(s,"e","Test2");
}
void Test3(){
	string s=Test("wwwwe",'w');
	AssertEqual(s,"e","Test3");
}
void Test4(){
	string s=Test("qwertyui",'w');
	AssertEqual(s,"q\nertyui","Test4");
}
void Test5(){
	string s=Test("1234,5678,1345",',');
	AssertEqual(s,"1234\n5678\n1345","Test5");
}
void Test6(){
	string s=Test("qwwwwwwwq",'w');
	AssertEqual(s,"q\nq","Test6");
}
void Test7(){
	string s=Test("qwwwwwww",'w');
	AssertEqual(s,"q","Test7");
}

void Test8(){
	string s=Test("qwe",'r');
	AssertEqual(s,"qwe","Test8");
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(Test1,"Test1");
	tr.RunTest(Test2,"Test2");
	tr.RunTest(Test3,"Test3");
	tr.RunTest(Test4,"Test4");
	tr.RunTest(Test5,"Test5");
	tr.RunTest(Test6,"Test6");
	tr.RunTest(Test7,"Test7");
	tr.RunTest(Test8,"Test8");
}

void Ignore(stringstream&ss,const char& c){
	while(ss.peek()==c){
		ss.ignore();
	}
}
vector <string> Func(stringstream& ss,const char& c){
	vector <string> V;
	Ignore(ss,c);
	while(!ss.eof()){
		string s;
		getline(ss,s,c);
		Ignore(ss,c);
		V.push_back(s);
	}
	return V;
}

void Print(const vector <string>& V){
	for(const auto& v: V){
		cout << v << endl;
	}
}

int main() {
	TestAll();
	stringstream ss;
	string str;
	char c;
	vector <string> V;
	cin >> str;
	ss << str;
	cin >> c;
	V=Func(ss,c);
	Print(V);
	return 0;
}
