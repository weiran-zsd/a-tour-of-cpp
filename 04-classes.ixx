#include <initializer_list>
#include <istream>
#include <iostream>
#include <list>
#include <vector>
export module _04_classes;

using namespace std;

// 具体类(concrete class)
class complex {
	double re, im;
public:
	complex(double r, double i):re{r},im{i}{}
	complex(double r):re{r},im{0}{}
	complex():re{0},im{0}{}
	double real() { return re; }
	double imag()const { return im; }
	void imag(double d) { im = d; }

	complex& operator+=(complex z) {
		re += z.re;
		im += z.im;
		return *this;
	}

	complex& operator-=(complex z) {
		re -= z.re;
		im -= z.im;
		return *this;
	}

	complex& operator*=(complex);
	complex& operator/=(complex);

};
complex operator+(complex a, complex b) { return a += b; }
complex operator-(complex a, complex b) { return a -= b; }
complex operator-(complex a) {return { -a.real(),-a.imag() };}
complex operator*(complex a, complex b) { return a *= b; }
complex operator/(complex a, complex b) { return a /= b; }

bool operator==(complex a, complex b) {
	return a.real() == b.real() && a.imag() == b.imag();
}

void f(complex z) {
	complex a{ 2, 3 };
	complex b{ 1 / a };
	complex c{ a + z * complex{1,2.3} };

	if (c != b) {
		c = -b/2;
	}
}

// 4.2.2 容器
// RAII
class Vector {
public:
	Vector(int s=0): elem{new double[s]}, sz{s} {
		for (int i = 0; i != s; i++) elem[i] = 0;
	};

	Vector(initializer_list<double> lst) : elem{ new double[lst.size()] }, sz{(int)lst.size()} {

	};
	void push_back(double d);

	~Vector() { delete[] elem; }
	double& operator[](int i) { return elem[i]; };
	int size()const { return sz; }

private:
	double* elem;
	int sz;
};

void fct(int n) {
	Vector v(n);

	{
		Vector v2(2 * n);
	}
}
// 4.2.3 初始化容器

Vector read(istream& is) {
	Vector v;
	for (double d; is >> d;) {
		v.push_back(d);
	}

	return v;
}

void foo() {
	Vector v = read(cin);
	Vector v1 = { 1,2,3,4,5 };
	Vector v2 = { 1.1, 3.2 };
}
// static_cast<int> vs. reinterpret_cast vs. const_cast

// 4.3 抽象类型(接口)
// vtbl
class Container {
public:
	virtual double& operator[](int) = 0;
	virtual int size() const = 0;
	virtual ~Container(){}
};

void use(Container& c) {
	const int sz = c.size();
	for (int i = 0; i != sz; i++) {
		cout << c[i] << "\n";
	}
}

class Vector_container : public Container {
public:
	Vector_container(int s): v(s) { }
	~Vector_container(){}
	double& operator[](int i)override { return v[i]; }
	int size()const override { return v.size(); }
private:
	Vector v;
};

void g() {
	Vector_container vc(10);
	use(vc);
}

class List_container : public Container {
public:
	List_container(initializer_list<double> il) : ld{ il } {}
	~List_container() {}
	double& operator[](int i) override {
		for (auto& x : ld) {
			if (i == 0) {
				return x;
			}
			i--;
		}
		throw out_of_range{ "list container." };
	};
	int size()const override { return ld.size(); }
private:
	list<double> ld;
};

void h() {
	List_container lc = { 1,2,3, };
	use(lc);
}

// 4.5 类层次
//    shape
//     / \
// circle triagnle
//   /
// smiley

class Point {};
class Shape {
public:
	virtual Point center()const = 0;
	virtual void move(Point to) = 0;
	virtual void draw() const = 0;
	virtual void rotate(int angle) = 0;
	virtual ~Shape(){}
};

void rotate_all(vector<Shape*>& v, int angle) {
	for (auto p : v) {
		p->rotate(angle);
	}
}

class Circle :public Shape {
public:
	Circle(Point p, int rad);
	Point center()const override {
		return x;
	}
	void move(Point to) {
		x = to;
	}
	void draw()const override;
	void rotate(int)override {};
private:
	Point x;
	int r;
};

class Smiley : public Circle {
public:
	Smiley(Point p, int rad) : Circle{ p,rad }, mouth(nullptr) {}
	~Smiley() {
		delete mouth;
		for (auto p : eyes) {
			delete p;
		}
	}
	void move(Point to);
	void draw()const {
		Circle::draw();
		for (auto p : eyes) {
;			p->draw();
		}
		mouth->draw();
	};
	void rotate(int);
	void add_eye(Shape* s) {
		eyes.push_back(s);
	}
	void set_mouth(Shape* s);
	virtual void wink(int i);
private:
	vector<Shape*> eyes;
	Shape* mouth;
};

// 4.5.1层次结构的益处
// a. 接口继承
// b. 实现继承


// 4.5.2 层次漫游
// dynamic_cast
Shape* read_shape(istream&);
Shape* ps{ read_shape(cin) };
void _f() {
	if (Smiley* p = dynamic_cast<Smiley*>(ps)) {
		// smiley
	}
	else {
		// not smiley
	}
}


// 4.5.3 避免资源泄露
void user(int x) {
	Shape* p = new Circle(Point(), 10);
	if (x == 0) return; // 潜在泄露危险

	delete p;
}

// unique_ptr;
class _Smiley {
//...
private:
	vector<unique_ptr<Shape>> eyes;
	unique_ptr<Shape> mouth;
};