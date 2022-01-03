#include <stdexcept>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <complex>

export module _03_module;

using namespace std;

export class Vector {
public:
	Vector(int s);
	double& operator[](int i);
	int size();
private:
	double* elem;
	int sz;
};

Vector::Vector(int s){
	if (s < 0) {
		throw length_error{ "Vector consturctor: negative size" };
	}
	elem = new double[s];
	sz = s;
}

double& Vector::operator[](int i) {
	if (i < 0 || i >= sz) {
		throw out_of_range("Vector::operator[]");
	}
	return elem[i];
}

int Vector::size() {
	return sz;
}

export int size(Vector& v) { return v.size(); }


// 3.4 命名空间

namespace My_code {
	class complex{};
}

My_code::complex c;

// 3.5 错误处理
// a. 异常

void f(Vector& v) noexcept{
	try {
		v[v.size()] = 7; // exp!
	}
	catch (out_of_range& err) {
		cout << err.what() << '\n';
	}
}

// b. 不变式

// c. 错误处理替代

// d. 合约
void fn(const char* p) {
	assert(p != nullptr);
}

// e. 静态断言
static_assert(sizeof(int) >= 4, "int are too small");

// 3.6 函数参数&返回值
// a. 参数传递 => 默认“传值”

void test(vector<int> v, vector<int>& rv) {
	v[1] = 99;
	rv[2] = 66;
}

void print(int value, int base = 10);
// b. 返回值

int& bad() {
	int x = 0;

	return x; //error! 返回局部变量的引用
}

class Matrix {};
Matrix operator+(const Matrix& x, const Matrix& y) {
	Matrix res;
	//...
	return res;
}

Matrix m1, m2;

Matrix m3 = m1 + m2; // copy

Matrix* add(const Matrix& x, const Matrix& y) {  // 1990s 风格 :)
	Matrix* p = new Matrix;
	//...
	return p;
}

void _f() {
	Matrix m1, m2;
	Matrix* pm = add(m1, m2);
	delete pm;
}


auto mul(int i, double d) { return i * d; }

// 3.6.3 结构化绑定
struct Entry {
	string name;
	int value;
};

Entry read_entry(istream& is) {
	string s;
	int i;
	is >> s >> i;
	return { s,i };
}

auto e = read_entry(cin);

void __fn() {
	auto [n, v] = read_entry(cin);

	map<string, int> m;
	for (const auto [key, value] : m) {
		cout << key << value << "\n";
	}

	std::complex<double> z = { 1,2 };
	auto e = z + 2.;
}
