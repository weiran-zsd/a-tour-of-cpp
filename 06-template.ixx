#include <stdexcept>
#include <list>
#include <complex>
#include <vector>
#include <iostream>

export module _06_template;
using namespace std;

template<typename T>
//template<Element T>
class Vector {
private:
	T* elem;
	int sz;
public:
	explicit Vector(int s) {
		elem = new T[s];
		sz = s;
	};
	Vector(initializer_list<T>);
	~Vector() { delete[] elem; }
	//...拷贝&移动

	T& operator[](int i);
	const T& operator[](int i) const {
		if (i < 0 || i >= size()) {
			throw out_of_range("vector:operator[]");
		}
		return elem[i];
	};
	int size()const { return sz; }

	T* begin() {
		return sz ? &elem[0] : nullptr;
	}
	T* end() {
		return sz ? &elem[0] + sz : nullptr;
	}
};


Vector<char> vc(200);
Vector<string> vs(17);
Vector<list<int>> vli(45);

// 6.2.1 约束模板参数(c++20)
// template<Element T>

// 6.2.2 值模板参数
template<typename T, int N>
struct Buffer {
	using value_type = T;
	constexpr int size() { return N; }
	//T[N];
};

Buffer<char, 1024> glob;



// 6.2.3 模板参数推断
pair<int,double> p = { 1, 5.2 };

auto p2 = make_pair(1, 5.2);

Vector v1{ 1,2,3 };
Vector v2 = v1;

auto pv = new Vector{ 1,2 };
Vector<string> vs1{ "hello", "world" };
Vector vss{ "hello", "world" }; // Vector<const char*>!!
Vector vs2{ "hello"s, "world"s };

template<typename T>
class Vector2 {
public:
	using value_type = T;
	Vector2(initializer_list<T>);
	template<typename lter>
	Vector2(lter b, lter e);
};

// 6.3 参数化操作
// 6.3.1 函数模板
template<typename Seq, typename Value>
Value sum(const Seq& s, Value v) {
	for (auto x : s) {
		v += x;
	}
	return v;
}

void user(vector<int>& vi, list<double>& ld, vector<complex<double>>& vc) {
	int x = sum(vi, 0);
	double d = sum(vi, 0.0);
	double dd = sum(ld, 0.0);
	auto z = sum(vc, complex{ 0.0, 0.0 });
}

// 6.3.2 函数对象
template<typename T>
class Less_than {
	const T val;
public:
	Less_than(const T& v): val{v}{}
	bool operator()(const T& x)const { return x < val; }
};

Less_than lti{ 42 };
Less_than lts{ "backus"s };
Less_than<string> lts2{ "naur" };

void fct(int n, const string& s) {
	bool b1 = lti(n);
	bool b2 = lts(s);
}

template<typename C, typename P>
int count(const C& c, P pred) {
	int cnt = 0;
	for (const auto& x : c) {
		if (pred(x)) cnt++;
	}
	return cnt;
}

void fct1(const vector<int>& vec, int x) {
	cout << count(vec, Less_than{x});
}

// c. lambda

void f(const vector<int>& vec, const list<string>& lst, int x, const string& s) {
	cout << count(vec, [&](int a) {return a < x; });
	cout << count(lst, [&](const string& a) {return a < s; });
}

template<typename C, typename Oper>
void for_all(C & c, Oper op) {
	for (auto& x : c) {
		op(x);
	}
}

class Shape {
	int i = 0; 
public:
	void draw(){}
	void rotate(int r);
};
void user2() {
	vector<unique_ptr<Shape>> v;
	for_all(v, [](unique_ptr<Shape>& ps) {ps->draw(); });
}

template<class S>
void rotate_and_draw(vector<S>& v, int r) {
	for_all(v, [&](auto& s) {s->rotate(r); s->draw(); });
}

void user4() {
	vector<unique_ptr<Shape>> v1;
	vector<Shape*> v2;

	rotate_and_draw(v1, 45);
	rotate_and_draw(v2, 89);
}

// 6.4 模板机制
// 6.4.1 可变参数模板
template<class T>
constexpr T viscosity = 0.2;

// 6.4.2 别名
//using size_t = unsigned int;
template<typename T>
class Vector3 {
public:
	using value_type = T;
	//...
};

template<typename C>
using Value_type = typename C::value_type;


template<typename Container>
void algo(Container& c) {
	Vector<Value_type<Container>> vec;
}

template<typename Key, typename Value>
class Map {
	//...
};

template<typename Value>
using String_map = Map<string, Value>;

String_map<int> m;

// 6.4.3 编译时if
template<typename T>
void update(T& target) {
	//..
	if constexpr (is_pd<T>::value) {
		simple_and_fast(target);
	}
	else {
		slow_and_safe(target);
	}
}