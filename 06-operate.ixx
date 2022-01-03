#include <string>
#include <complex>
#include <complex>
#include <thread>
#include <cassert>
import _03_module;
export module _06_operate;

using namespace std;

class X {
public:
	X(int);
	X();
	X(const X&);
	X(X&&);
	X& operator=(const X&);
	X& operator=(X&&);
	~X();
	//...
};
//�ƶ� / ������
// a. ��ֵ
// b. �����ʼֵ
// c. ����ʵ��
// d. ��������ֵ
// e. ��Ϊ�쳣

class Y {
public:
	Y(int);
	Y(const Y&) = default;
	Y(Y&) = default;
	Y(Y&&) = default;
};

// the rule of  zero: Ҫô�������У�Ҫô1��Ҳ�����壻
struct Z {
	Vector v;
	string s;
};

void f() {
	Z z1(10);
	Z z2 = z1;
}

class Shape {
public:
	Shape(const Shape&) = delete; // �޿�������
};

// 5.1.2 ����ת��
complex z1 = 3;
complex z2 = z1 * 1;

Vector v1 = 7;
class V {
public:
	explicit V(int s); // ��ֹ int -> vector����ʽת��
};

// 5.1.3 ��Ա��ʼֵ
class cmplx {
	double re = 0;
	double im = 0;
public:
	cmplx(double r, double i): re{r}, im{i}{}
	cmplx(double r): re{r} {}
	cmplx(){}
};

// 5.2 ����&�ƶ�
void bad_copy(Vector v1) {
	Vector v2 = v1;
	v1[0] = 2;
	v2[1] = 3;
}

class _V {
public:
	_V();
	_V(int s);
	~_V() { delete[] elem; }
	_V(const _V& a); // �������캯��
	_V& operator=(const _V& a); // ������ֵ�����
	double& operator[](int i) { return elem[i]; }
	_V operator+(_V& a) {
		_V res(sz);
		for (int i = 0; i != a.sz; i++) {
			res[i] = elem[i] + a[i];
		}
		return res;
	}

	_V(_V&& a) {// �ƶ����캯��
		elem = a.elem;
		sz = a.sz;
		a.elem = nullptr;
		a.sz = 0;
	}; 

	_V& operator=(_V&& a){// �ƶ���ֵ�����
		elem = a.elem;
		sz = a.sz;
		a.elem = nullptr;
		a.sz = 0;
		return *this;
	}

	double* elem;
	int sz;
};

_V::_V(const _V& a){
	elem = new double[a.sz];
	sz = a.sz;
	for (int i = 0; i != sz; i++) {
		elem[i] = a.elem[i];
	}
}

_V& _V::operator=(const _V& a) {
	double* p = new double[a.sz];
	for (int i = 0; i != a.sz; i++) {
		p[i] = a.elem[i];
	}
	delete[] elem;
	elem = p;
	sz = a.sz;
	return *this;
}

// 5.2.2�ƶ�����

_V f(_V& x, _V& y, _V& z) {
	_V r;
	r = x + y + z;

	_V a(100);
	_V b(200);
	_V c(200);
	c = a; // ����
	b = std::move(a); // �ƶ���ֵ

	return c; // �ƶ�
}

// 5.3 ��Դ����
vector<thread> my_threads;
Vector init(int n) {
	thread t;
	my_threads.push_back(move(t));

	Vector vec(n);
	for (int i = 0; i != vec.size(); i++) {
		vec[i] = 777;
	}
	return vec;
}

auto v = init(1'000'000);

// 5.4 �������
// a. ==,!=, <, <=, >, >=
// b. size(), begin(), end(),
// c. >>, <<
// d. udl
// e. swap()
// f. hash<>

// 5.4.1 �Ƚ�
void _5_4_1() {
	int i = 0;
	int j = i;
	assert(i==j);
}
// 5.4.2 ��������
void _5_4_2(vector<int> c) {
	for (size_t i = 0; i < c.size(); i++) {
		c[i] = 0;
	}

	for (auto p = c.begin(); p != c.end(); p++) {
		*p = 0;
	}

	for (auto& x : c) {
		x = 0;
	}
}

// 5.4.3 io

// 5.4.4 �û��Զ�������ֵ
constexpr complex<double> operator""i(long double arg) {
	return { 0, arg };
}

complex<double> z = 1.1 + 6.2i;

