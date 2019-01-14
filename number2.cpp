#include "TestingFramework.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

uint64_t PRNG();
vector <int64_t> Numb();
int64_t Mean_arithmetic(vector <int64_t>& Number);

void Test1(){
	vector <int64_t> Number=Numb();
	char c('0');
	for(const auto& n:Number){
		if(n>INT_MAX||n<INT_MIN){
			c='1';
		}
	}
	AssertEqual(c,'0',"Test1");
}

void Test2(){
	vector <int64_t> Number=Numb();
	char c('0');
	auto Max=max_element(Number.begin(),Number.end());
	if(*Max>INT_MAX){
		c='1';
	}
	AssertEqual(c,'0',"Test1");
}

void Test3(){
	vector <int64_t> Number=Numb();
	char c('0');
	auto Min=min_element(Number.begin(),Number.end());
	if(*Min<INT_MIN){
		c='1';
	}
	AssertEqual(c,'0',"Test1");
}

void TestAll(){
	TestRunner tr;
	tr.RunTest(Test1,"Test1");
	tr.RunTest(Test2,"Test2");
	tr.RunTest(Test3,"Test3");
}

vector <int64_t> Numb(){
	vector <int64_t> Number(100);
	for(auto& number:Number){
		number=PRNG();
	}
	return Number;
}

int64_t Mean_arithmetic(vector <int64_t>& Number){
	int64_t sum=0;
	for(const auto& number:Number){
		sum+=number;
	}
	return sum/Number.size();
}

uint64_t PRNG(){
	static uint64_t seed = time(NULL);
	seed=(8253729*seed+2396403);
	int64_t Max=INT_MAX;
	Max=2*Max;
	int64_t Min=INT_MIN;
	return seed%Max+Min;
}

int main() {
	TestAll();
	srand(time(NULL));
	vector <int64_t> Number=Numb();
	int64_t mean_arithmetic=Mean_arithmetic(Number);
	auto Max=max_element(Number.begin(),Number.end());
	auto Min=min_element(Number.begin(),Number.end());
	cout <<"mean_arithmetic: " << mean_arithmetic << endl;
	cout <<"max: " << *Max << endl;
	cout <<"min: " << *Min << endl;
	return 0;
}
