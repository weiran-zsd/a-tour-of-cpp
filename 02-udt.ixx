#include <iostream>
#include <variant>

using namespace std;

export module _02_udt;
// 2.1 struct
struct sVector {
	int sz;
	double* elem;
};

void vector_init(sVector& v, int s) {
	v.elem = new double[s];
	v.sz = s;
}

double read_and_sum(int s) {
	sVector v;
	vector_init(v, s);

	for (int i = 0; i != s; i++) {
		cin >> v.elem[i];
	}

	double sum = 0;
	for (int i = 0; i != s; i++) {
		sum += v.elem[i];
	}
	return sum;
}


void f(sVector v, sVector& rv, sVector* pv) {
	int i1 = v.sz;
	int i2 = rv.sz;
	int i3 = pv->sz;
}

// 2.3 class

class Vector {
public:
	Vector(int s) : elem{ new double[s] }, sz{ s } {};
	double& operator[](int i) { return elem[i]; };
	int size() { return sz; }
private:
	double* elem;
	int sz;
};


// 2.4 联合(union)

enum Type {ptr, num};
struct Node{};
union Value {
	Node* p;
	int i;
};

struct Entry {
	string name;
	Type t;
	Value v;
};

void f(Entry* pe) {
	if (pe->t == num) {
		cout << pe->v.i;
	}
}

// 推荐使用 variant!!
struct v_entry {
	string name;
	variant<Node*, int> v;
};

void v_f(v_entry* pe) {
	if (holds_alternative<int>(pe->v)) {
		cout << get<int>(pe->v);
	}
}

// 2.5 枚举
enum class Color {red, blue, green};
enum class Traffic_light {green, yellow, red};
Color col = Color::red;
Traffic_light light = Traffic_light::red;

//int i = Color::red; // error!
//Color c = 2; // error!

Color x = Color{ 5 };
Color y{ 6 };

// 定义运算符
Traffic_light& operator++(Traffic_light& t) {
	switch (t) {
	case Traffic_light::green: return t = Traffic_light::yellow;
	case Traffic_light::yellow: return t = Traffic_light::red;
	case Traffic_light::red: return t = Traffic_light::green;
	}
}

Traffic_light next = ++light;

// C-style
enum Colr {red, green, blue};
int c = green;