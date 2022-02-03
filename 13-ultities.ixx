export module _13_ultities;
import _04_classes;

//13.2 资源管理

#include <iostream>;
#include <mutex>;
#include <fstream>;
#include <span>
#include <array>;
#include <bitset>;
#include <variant>;
#include <any>
#include <list>;
#include <memory_resource>;
#include <chrono>;
#include <functional>;
#include <limits>;
#include <type_traits>;

using namespace std;

mutex m;
class X { int num=0; };
void f(int i) {
	scoped_lock<mutex> lck{ m };
	//...

	X* p = new X;
	unique_ptr<X> sp{ new X };

	if (i < 99) throw 100; // => p 内存泄露

	delete p;
}

unique_ptr<X> make_X(int i) {
	//...
	return unique_ptr<X>{new X{}};
}

void f(shared_ptr<fstream>);
void g(shared_ptr<fstream>);

void user(const string& name, ios_base::openmode mode) {
	shared_ptr<fstream> fp{ new fstream(name,mode) };
	if (!*fp) {
		throw 0;
	}

	f(fp);
	g(fp);
}

struct S {
	int i;
	string s;
	double d;
};

void f2() {
	shared_ptr<S> p1 = make_shared<S>(1, "ankn", 1.2);
	auto p2 = make_shared<S>(2, "oz", 7.2);
}

void f3() {
	auto p = make_unique<int>(2);
	//auto q = p; // ==> err
	auto q = move(p);
}

void fn() {
	string s1 = "hello";
	string s2 = "world";
	vector<string> v;
	v.push_back(s1);
	v.push_back(move(s2));
}

// 13.3 范围检查 span
void fpn(int* p, int n) {
	for (int i = 0; i < n; i++) {
		p[i] = 0;
	}
}

void fs(span<int> p) {
	for (int x : p) {
		x = 0;
	}
}

// 13.4 特殊容器
void f4() {
	array<int, 3> a1 = { 1,2,3 };

	bitset<9> bs1{ "1001100000" };
	bitset<9> bs2{ 0b1'1000'1111 };

	bitset<9> bs3 = ~bs1;
	bitset<9> bs4 = bs1 & bs3;
	bitset<9> bs5 = bs1 << 2;
}

//template<typename Forward_iterator, typename T, typename Compare>
//pair<Forward_iterator, Forward_iterator>
//equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);

struct Record { string name; };
auto less = [](const Record& r1, const Record& r2) {return r1.name < r2.name; };

void f43(const vector<Record>& v) {
	auto er = equal_range(v.begin(), v.end(), Record{ "Reg" }, ::less);
	for (auto p = er.first; p != er.second; p++) {
		cout << p->name;
	}
}

void f44(const vector<Record>& v) {
	auto [first, last] = equal_range(v.begin(), v.end(), Record{ "Reg" }, ::less);
	for (auto p = first; p != last; p++) {
		cout << p->name;
	}

	pair p1{ v.begin(), 2 };
	auto p2 = make_pair(v.begin(), 2);

	tuple<string, int, double> t1{ "shark", 123, 1.2 };
	auto t2 = make_tuple("herr", 10, 1.2);
	tuple t3{ "co"s, 2, 3.1 };

	string s = get<0>(t1);
	int x = get<1>(t1);
	double d = get<2>(t1);

	auto s1 = get<string>(t1);
	auto x1 = get<int>(t1);
	auto d1 = get<double>(t1);

	get<string>(t1) = "tu";
}

// 13.5 选择
variant<string, int> compose_messsage(istream& s) {
	string mess;
	//...
	bool no_problems = true;
	int err_num = 1;
	if (no_problems) {
		return mess;
	}
	else {
		return err_num;
	}
}

void f51() {
	auto m = compose_messsage(cin);
	if (holds_alternative<string>(m)) {
		cout << get<string>(m);
	}
	else {
		int err = get<int>(m);
	}
}

//using Node = variant<Expression, Statement, Declaration, Type>;
//void check(Node* p) {
//	if (holds_alternative<Expression>(*p)) {
//		Expression& e = get<Expression>(*p);
//	}
//	else if (holds_alternative<Statement>(*p)) {
//		Statement& s = get<Statement>(*p);
//	}
//}

optional<string> compose_msg(istream& s) {
	string mess;
	//...
	bool no_problems = true;
	int err_num = 1;
	if (no_problems) {
		return mess;
	}
	return {};
}

any comp_msg(istream& s) {
	if (s) {
		return true;
	}
	else {
		return "1";
	}
}

void f52() {
	auto m = comp_msg(cin);
	string s = any_cast<string>(m);
	cout << s;
}

// 13.6 分配器
struct Event {
	vector<int> data = vector<int>(512);
};

list<shared_ptr<Event>> q;

void producer(int n) {
	for (int i = 0; i != n; i++) {
		lock_guard lk{ m };
		q.push_back(make_shared<Event>());
		//cv.notify_one();
	}
}

//// pool
//pmr::synchronized_pool_resource pool;
//struct E{
//	vector<int> data = vector<int>(512, &pool);
//};
//list<shared_ptr<E>> qm{ &pool };

// 13.7 时间
using namespace std::chrono;
using namespace std::literals::chrono_literals;

auto t0 = high_resolution_clock::now();
auto spring_day = 42d;

// 13.8 函数适配器
void f81(vector<Shape*>& v) {
	for_each(v.begin(), v.end(), [](Shape* p) {p->draw(); });
}

void f82(vector<Shape*>& v) {
	for_each(v.begin(), v.end(), mem_fn(&Shape::draw));
}

int _f1(double);
int _f2(string);
void f83() {
	// 不能重载；
	function<int(double)> fct1{ _f1 };
	function fct2{ _f2 };
	function fct3 = [](Shape* p) {p->draw(); };
}

// 13.9 类型函数
void f91() {
	constexpr float min = numeric_limits<float>::min();
	constexpr int szi = sizeof(int);
}
// iterator_traits
// TODO!


// 类型谓词
void f93() {
	bool b1 = std::is_arithmetic<int>(); // true
	bool b2 = std::is_arithmetic<string>(); // false
}

template<typename Scalar>
class complex {
	Scalar re, im;
public:
	static_assert(is_arithmetic<Scalar>(), "sorry, only support complex of arithmetic types.");
	//...
};

template<typename T>
constexpr bool is_arithmetic() {
	return std::is_arithmetic<T>();
}

// enable_if => SFINAE
template<typename T>
class Smart_pointer {
	T& operator*();
	T& operator->();
};