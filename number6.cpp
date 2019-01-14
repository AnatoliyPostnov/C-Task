#include <iostream>
#include <vector>
using namespace std;

struct Vector{
	Vector()
		:x_(0)
		,y_(0)
		,z_(0){
	}
	Vector(const double& x,const double& y,const double& z)
		:x_(x)
		,y_(y)
		,z_(z){
	}
	double x_,y_,z_;
};

class Matrix{
public:
	Matrix(){}
	Matrix(const vector<vector<double>>& elements)
		:elements_(elements){
		if(elements_.size()!=3||elements_[0].size()!=3){
			throw invalid_argument("matrix.size()!=3");
		}
	}
	vector<vector<double>> get_elements() const{
		return elements_;
	}
	void Print_elements() const{
		for(const auto& e:elements_){
			for(const auto c:e){
				cout << c << " ";
			}
			cout << endl;
		}
	}
private:
	vector<vector<double>> elements_;
};

Vector operator * (const Vector& v1,const Vector& v2){
	Vector v;
	v.x_=v1.y_*v2.z_-v1.z_*v2.y_;
	v.y_=v1.z_*v2.x_-v1.x_*v2.z_;
	v.z_=v1.x_*v2.y_-v1.y_*v2.x_;
	return v;
}

Vector operator * (const double& c,const Vector& v1){
	return {c*v1.x_,c*v1.y_,c*v1.z_};
}

Vector operator * (const Vector& v1,const double& c){
	return {c*v1.x_,c*v1.y_,c*v1.z_};
}

Matrix operator * (const Matrix& m1,const Matrix& m2){
	vector<vector<double>> a=m1.get_elements();
	vector<vector<double>> b=m2.get_elements();
	Matrix m({
		{a[0][0]*b[0][0]+a[0][1]*b[1][0]+a[0][2]*b[2][0]
		,a[0][0]*b[0][1]+a[0][1]*b[1][1]+a[0][2]*b[2][1]
		,a[0][0]*b[0][2]+a[0][1]*b[1][2]+a[0][2]*b[2][2]},
		{a[1][0]*b[0][0]+a[1][1]*b[1][0]+a[1][2]*b[2][0]
		,a[1][0]*b[0][1]+a[1][1]*b[1][1]+a[1][2]*b[2][1]
		,a[1][0]*b[0][2]+a[1][1]*b[1][2]+a[1][2]*b[2][2]},
		{a[2][0]*b[0][0]+a[2][1]*b[1][0]+a[2][2]*b[2][0]
		,a[2][0]*b[0][1]+a[2][1]*b[1][1]+a[2][2]*b[2][1]
		,a[2][0]*b[0][2]+a[2][1]*b[1][2]+a[2][2]*b[2][2]}
	});
	return m;
}

Vector operator * (const Matrix& m,const Vector& v){
	vector <vector<double>> a = m.get_elements();
	Vector vec(a[0][0]*v.x_+a[0][1]*v.y_+a[0][2]*v.z_
			   ,a[1][0]*v.x_+a[1][1]*v.y_+a[1][2]*v.z_
			   ,a[2][0]*v.x_+a[2][1]*v.y_+a[2][2]*v.z_);
	return vec;
}

ostream& operator << (ostream& os,const Matrix& m){
	vector<vector<double>> a=m.get_elements();
	os << "{" <<a[0][0] << "; " << a[0][1] << "; " << a[0][2] << "}" << endl;
	os << "{" <<a[1][0] << "; " << a[1][1] << "; " << a[1][2] << "}" << endl;
	os << "{" <<a[2][0] << "; " << a[2][1] << "; " << a[2][2] << "}" << endl;
	return os;
}
ostream& operator << (ostream& os,const Vector& v){
	os << "{" <<v.x_ << "; " << v.y_ << "; " << v.z_ << "}" << endl;
	return os;
}

double scalar_vector(const Vector& v1,const Vector& v2){
	return v1.x_*v2.x_+v1.y_*v2.y_+v1.z_*v2.z_;
}

Matrix operator + (const Matrix& m1,const Matrix& m2){
	vector<vector<double>> a=m1.get_elements();
	vector<vector<double>> b=m2.get_elements();
	Matrix m({
		{a[0][0]+b[0][0],a[0][1]+b[0][1],a[0][2]+b[0][2]}
		,{a[1][0]+b[1][0],a[1][1]+b[1][1],a[1][2]+b[1][2]}
		,{a[2][0]+b[2][0],a[2][1]+b[2][1],a[2][2]+b[2][2]}
	});
	return m;
}

Matrix operator - (const Matrix& m1,const Matrix& m2){
	vector<vector<double>> a=m1.get_elements();
	vector<vector<double>> b=m2.get_elements();
	Matrix m({
		{a[0][0]-b[0][0],a[0][1]-b[0][1],a[0][2]-b[0][2]}
		,{a[1][0]-b[1][0],a[1][1]-b[1][1],a[1][2]-b[1][2]}
		,{a[2][0]-b[2][0],a[2][1]-b[2][1],a[2][2]-b[2][2]}
	});
	return m;
}
Vector operator + (const Vector& v1,const Vector& v2){
	Vector v;
	v.x_=v1.x_+v2.x_;
	v.y_=v1.y_+v2.y_;
	v.z_=v1.z_+v2.z_;
	return v;
}

Vector operator - (const Vector& v1,const Vector& v2){
	Vector v;
	v.x_=v1.x_-v2.x_;
	v.y_=v1.y_-v2.y_;
	v.z_=v1.z_-v2.z_;
	return v;
}

int main() {
	Vector v1(1,2,3),v2(4,5,6);
	cout << "v1=" << v1;
	cout << "v2=" << v2;
	Matrix m1({{1,2,3}
			 ,{4,5,6}
			 ,{7,8,9}});
	cout << "m1=" << endl;
	m1.Print_elements();
	Matrix m2({{1,2,3}
			 ,{4,5,6}
			 ,{7,8,9}});
	cout << "m2=" << endl;
	m2.Print_elements();
	cout << "m1*v1+m2*v2=";
	cout << m1*v1+m2*v2;
	cout << "m1+m2=" << endl;
	cout << m1+m2;
	cout << "m1*m2=" << endl;
	cout << m1*m2;
	cout << "m1*v1+v2=";
	cout << m1*v1+v2;
	cout << "v1*v2=";
	cout << v1*v2;
	cout << "scalar * (v1*v2) = ";
	cout << scalar_vector(v1,v2);
	return 0;
}
