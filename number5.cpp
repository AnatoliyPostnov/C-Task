#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>

using namespace std;

struct point{
	point()
		:x(0)
		,y(0){
	}
	double x;
	double y;
};

void Scanf(point& point1,point& point2,point& point3){
	cout << "Enter the coordinates of the points: " << endl;
	cout << "x1: ";
	cin >> point1.x;
	cout << "y1: ";
	cin >> point1.y;
	cout << "x2: ";
	cin >> point2.x;
	cout << "y2: ";
	cin >> point2.y;
	cout << "x3: ";
	cin >> point3.x;
	cout << "y3: ";
	cin >> point3.y;
}

bool operator < (const point& point1,const point& point2){
	if(point1.x<point2.x){
		return true;
	}else{
		return false;
	}
}

bool operator != (const point& point1,const point& point2){
	if(point1.x==point2.x&&point1.y==point2.y){
		return false;
	}else{
		return true;
	}
}

point Middle(const vector<point>& elements,const point& min,const point& max){
	point p;
	for(const auto& e:elements){
		if(e!=min&&e!=max){
			p=e;
		}
	}
	return p;
}

vector<pair<double,double>> T_func(const vector<point>& elements,const vector<double>& elem){
	vector<pair<double,double>> T;
	for(const auto&e:elem){
		double denominator=elements[0].x-2*elements[1].x+elements[2].x;
		if(denominator==0){
			throw invalid_argument("denominator == 0");
		}
		double d=(elements[0].x-2*elements[1].x+elements[2].x)*e+
					pow(elements[1].x,2)-elements[0].x*elements[2].x;
		if(d<0){
			throw invalid_argument("discriminant < 0");
		}
		double t1=(elements[0].x-elements[1].x-sqrt(d))/denominator;
		double t2=(elements[0].x-elements[1].x+sqrt(d))/denominator;
		pair<double,double> t(t1,t2);
		T.push_back(t);
	}
	return T;
}

vector<pair<double,double>> Y_func(const vector<pair<double,double>>& T,const vector<point>& elements){
	vector<pair<double,double>> Y;
	for(const auto&t:T){
		double y1=pow(1-t.first,2)*elements[0].y+
					2*t.first*(1-t.first)*elements[1].y+
					pow(t.first,2)*elements[2].y;
		double y2=pow(1-t.second,2)*elements[0].y+
					2*t.second*(1-t.second)*elements[1].y+
					pow(t.second,2)*elements[2].y;
		pair<double,double> y(y1,y2);
		Y.push_back(y);
	}
	return Y;
}

void Print(const vector<double>& elem,const vector<pair<double,double>>& Y){
	int i=0;
	for(const auto& y:Y){
		cout << "x= " << elem[i]<< " y1= " <<y.first << " y2= " << y.second << endl;
		++i;
	}
}

int main() {
	point point1,point2,point3;
	Scanf(point1,point2,point3);
	vector<point> elements{point1,point2,point3};
	vector<double> elem;
	point min=*(min_element(elements.begin(),elements.end()));
	point max=*(max_element(elements.begin(),elements.end()));
	point middle=Middle(elements,min,max);
	elements.clear();
	elements={min,middle,max};
	for(int i=ceil(min.x);i<=floor(max.x);++i){
		elem.push_back(i);
	}
	vector<pair<double,double>> T=T_func(elements,elem);
	vector<pair<double,double>> Y=Y_func(T,elements);
	Print(elem,Y);
	return 0;
}
