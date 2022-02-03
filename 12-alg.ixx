#include <vector>;
#include <string>;
#include <list>;
#include <algorithm>;
#include <iomanip>;
#include <iostream>;
#include <fstream>;
#include <set>;
#include <map>
#include <ranges>;
#include <execution>;
export module _12_alg;

using namespace std;

struct Entry {
	string name;
	int number;
};

bool operator<(const Entry& x, const Entry& y) {
	return x.name < y.name;
}
bool operator==(const Entry& x, const Entry& y) {
	return x.name == y.name;
}

void f(vector<Entry>& vec, list<Entry>& lst) {
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), lst.begin());
}

list<Entry> f(vector<Entry> vec) {
	list<Entry> res;
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), back_inserter(res));
	return res;
}

// 12.2 迭代器
bool has_c(string& s, char c) {
	auto p = find(s.begin(), s.end(), c);
	return p != s.end();
}

vector<string::iterator> find_all(string& s, char c) {
	vector<string::iterator> res;
	for (auto p = s.begin(); p != s.end(); p++) {
		if (*p == c) res.push_back(p);
	}
	return res;
}

template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v) {
	vector<typename C::iterator> res;
	for (auto p = c.begin(); p != c.end(); p++) {
		if (*p == c) res.push_back(p);
	}
	return res;
}

// 12.3 迭代器类型

// 12.4 流迭代器
void f4() {
	ostream_iterator<string> oo{ cout };
	*oo = "hello";
	oo++;
	*oo = "world";

	istream_iterator<string> ii = { cin };
	istream_iterator<string> eos = {}; // 结束

}

int f41() {
	string from, to;
	cin >> from >> to;

	ifstream is(from);
	istream_iterator<string> ii { is };
	istream_iterator<string> eos{};

	ofstream os{ to };
	ostream_iterator<string> oo{ os, "\n" };

	vector<string> b{ ii, eos };
	sort(b.begin(), b.end());

	unique_copy(b.begin(), b.end(), oo);

	return !is.eof() || !os;
}

int f42() {
	string from, to;
	cin >> from >> to;

	ifstream is{ from };
	ofstream os{ to };

	set<string> b{ istream_iterator<string> {is}, istream_iterator<string>{} };
	copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"});
	return !is.eof() || !os;
}

// 12.5 谓词
struct Greater_than {
	int val;
	Greater_than(int v) : val{ v } {}
	bool operator()(const pair<string, int>& r)const { return r.second > val; }
};

void f5(map<string, int>& m) {
	auto p = find_if(m.begin(), m.end(), Greater_than{ 42 });
	auto p1 = find_if(m.begin(), m.end(), [](const pair<string, int>& r) {return r.second > 42; }); // lambda
}


// 12.7 概念(concept)

template<typename R>
requires sortable<R>
void sort(R& r) {
	return sort(begin(r), end(r));
}


// 12.8 容器算法
namespace estd {
	template<typename C>
	void sort(C& c) {
		sort(c.begin(), c.end());
	}

	template<typename C, typename Pred>
	void sort(C& c, Pred p) {
		sort(c.begin(), c.end(), p);
	}
}
// 12.9 并行算法

void f(vector<int> v) {
	sort(v.begin(), v.end());
	sort(execution::seq, v.begin(), v.end());
	sort(execution::par, v.begin(), v.end());
	sort(execution::unseq, v.begin(), v.end());
}