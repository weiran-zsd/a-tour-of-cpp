#include <string>;
#include <iostream>
#include <uchar.h>
#include <regex>

export module _09_string;


using namespace std;

string compose(const string& name, const string& domain){
	return name + "@" + domain;
}

auto addr = compose("dmr", "bell-labs.com");

void m2(string& s1, string& s2) {
	s1 = s1 + '\n';
	s2 += '\n';
}

string name = "niels stroustrup";
void m3() {
	string s = name.substr(6, 10);
	name.replace(0, 5, "nicholas");
	name[0] = toupper(name[0]);
}

string incantation;
void respond(const string& answer){
	if (answer == incantation) {
	}
	else if(answer == "yes") {

	}
}

void print(const string& s) {
	printf("for people who like printf: %s\n", s.c_str());
	cout << "for people who like streams" << s << '\n';
}

// string的实现 短字符优化（short-string opt)

// basic_string

//using Jstring = basic_string<Jchar>;

// 9.3 string_view

string cat(string_view sv1, string_view sv2) {
	string res;
	res.resize(sv1.length() + sv2.length());
	char* p = &res[0];
	for (char c : sv1) {
		*p++ = c;
	}
	copy(sv2.begin(), sv2.end(), p);
	return res;
}

void m() {
	string king = "harold";
	auto s1 = cat(king, "william");
	auto s2 = cat(king, king);
	auto s3 = cat("ed", "ste"sv);
	auto s4 = cat("canute"sv, king);
	auto s5 = cat({ &king[0], 2 }, "henry"sv);
	auto s6 = cat({ &king[0], 2 }, { &king[2], 4 });
}

// 9.4 regexp
regex pat{ R"(\w{2})" };

// 9.4.1 搜索

void sfn() {
	int lineno = 0;
	for (string line; getline(cin, line);) {
		lineno++;
		smatch matches;
		if (regex_search(line, matches, pat)) {
			cout << lineno << ": " << matches[0] << '\n';
		}
	}
}

bool is_identiier(const string& s) {
	regex pat{ R"([_[:alpha:]]\w*)" };
	return regex_match(s, pat);
}

void test() {
	string input = "aa as; asd ++e^asdf asdfg";
	regex pat{ R"(\s+(\w)+)" };
	for (sregex_iterator p(input.begin(), input.end(), pat); p != sregex_iterator{}; p++) {
		cout << (*p)[1] << '\n';
	}
}