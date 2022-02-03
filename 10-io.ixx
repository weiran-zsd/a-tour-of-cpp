export module _10_io;

#include <iostream>;
#include <sstream>;
#include <vector>;
#include <fstream>;
#include <exception>;
#include <cstdio>;
#include <filesystem>;
#include <cassert>

using namespace std;
using namespace filesystem;

void f() {
	cout << 10;
	int x{ 10 };
	cout << x;

	int i;
	cin >> i;
	
	string str;
	cin >> str;
	getline(cin, str);
}

// 10.4 i/o状态
vector<int> read_ints(istream& is, const string& terminator) {
	vector<int> res;
	for (int i; is >> i;) {
		res.push_back(i);
	}
	if (is.eof()) {
		return res;
	}

	if (is.fail()) {
		is.clear();
		is.unget();
		string s;
		if (cin >> s && s == terminator) {
			return res;
		}
		cin.setstate(ios_base::failbit);
	}
	return res;
}

// 10.5 用户定义类型i/o
struct Entry {
	string name;
	int number;
};

ostream& operator<<(ostream& os, const Entry& e) {
	return os << "{\"" << e.name << "\", " << e.number << "";
}

istream& operator>>(istream& is, Entry& e) {
	char c, c2;
	if (is >> c && c == '{' && is >> c2 && c2 == '"') {
		string name;
		while (is.get(c) && c != '"') {
			name += c;
		}
		if (is >> c && c == ',') {
			int number = 0;
			if (is >> number >> c && c == '}') {
				e = { name, number };
				return is;
			}
		}
	}
	is.setstate(ios_base::failbit);
	return is;
}

// 10.6 格式化
void fmt() {
	double d = 12.333;
	cout << d << ";"
		<< scientific << d << ";"
		<< hexfloat << d << ";"
		<< fixed << d << ";"
		<< defaultfloat << d << ";";
}

// 10.7 文件流

void fs() {
	ofstream ofs{ "target" };
}

// 10.8 字符串流
void test() {
	ostringstream oss;
	oss << "{temp," << scientific << 12.333 << "}";
	cout << oss.str() << '\n';
}

template<typename Target=string, typename Source=string>
Target to(Source arg) {
	stringstream inter;
	Target result;

	if (!(inter << arg) || !(inter >> result) || !(inter >> std::ws).eof()) {
		throw runtime_error{ "to<>() failed" };
	}
	return result;
}

// 10.9 c-style i/o
void f9() {
	ios_base::sync_with_stdio(false);
}

// 10.10 fs

void fs10() {
	path f = "C:/hy.cpp";
	assert(exists(f));

	if (is_regular_file(f)) {
		cout << f << file_size(f);
	}
}

void print_dir(path p) {
	try {
		if (is_directory(p)) {
			cout << p << ":\n";
			for (const directory_entry& x : directory_iterator{ p }) {
				cout << "  " << x.path() << "\n";
			}
		}
	}
	catch (const filesystem_error& ex) {
		cerr << ex.what() << '\n';
	}
}

