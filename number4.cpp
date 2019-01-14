#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ifstream file("C:\\Users\\xiaomi\\Desktop\\mytona\\number4\\main\\src\\input.txt");
	if (!file){
		cout << "Файл не открыт\n";
	 return 0;
	} else{
		cout << "Все ОК! Файл открыт!\n";
	}
	vector<string> v;
	while(!file.eof()){
		string s1,s2;
		do{
			s1.push_back(file.get());
		}while(file.peek()!=':');
		file.ignore();
		do{
			s2.push_back(file.get());
		}while(file.peek()!='\n'&&!file.eof());
		file.ignore();
		v.push_back("key: "+s1+" Value: "+s2);
	}
	for(const auto& v_:v){
		cout << v_ << endl;
	}
	file.close();
	return 0;
}
