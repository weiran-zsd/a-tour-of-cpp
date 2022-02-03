export module _11_container;
#include <iostream>;
#include <vector>;
#include <list>
#include <forward_list>
#include <map>;
#include <unordered_map>;
#include <unordered_set>;

using namespace std;

// 11.2 vector
struct Entry {
	string name;
	int number;
};

vector<Entry> phonebook = {
	{"Davild", 123},
};
ostream& operator<<(ostream& os, const Entry& e) {
	return os << "{\"" << e.name << "\", " << e.number << "";
}
void print_book(const vector<Entry>& book) {
	for (int i = 0; i != book.size(); i++) {
		cout << book[i] << '\n';
	}

	for (const auto& x : book) {
		cout << x << '\n';
	}
	vector<int> v1 = { 1,2,3, };
	vector<string> v2;
	vector<double> v4(1.2);

	v1.at(10); // -> error £º·¶Î§¼ì²é
}


// 11.3 list
int f3() {
	list<Entry> phonebook = { {"david"s, 123} };

	string s = "xxx";
	for (const auto& x : phonebook) {
		if (x.name == s) return x.number;
	}
	return 0;

	for (auto p = phonebook.begin(); p != phonebook.end(); p++) {
		if ((*p).name == s) return (*p).number;
	}
	return 0;


	list<Entry>::iterator p;
	Entry ee;
	phonebook.insert(p, ee);
	phonebook.erase(p);

	forward_list<Entry> fl;
	fl.push_front(ee);

}

// 11.4 map
// rb-tree
void f4() {
	map<string, int> phonebook{
		{"david", 1234}
	};

	phonebook.insert({ "bob", 1122 });
}

// 11.5 unordered_map (hash)
void f5() {
	unordered_map<string,int> phonebook;
	phonebook.insert({ "bob", 0 });

	int num = phonebook["bob"];
}

struct Record {
	string name;
	int product_code;
};

struct Rhash {
	size_t operator()(const Record& r) const {
		return hash<string>()(r.name) ^ hash<int>()(r.product_code);
	}
};

void f51() {
	unordered_set<Record, Rhash> my_set;
}

namespace std {
	template<> struct hash<Record> {
		using argument_type = Record;
		using result_type = std::size_t;
		size_t operator()(const Record& r) const {
			return hash<string>()(r.name) ^ hash<int>()(r.product_code);
		}
	};
}

// 11.6 ÈÝÆ÷¸ÅÊö
