export module _14_value;

#include <cmath>;
#include <iostream>;
#include <numeric>;
#include <list>
#include <vector>
#include <execution>;
#include <complex>;
#include <random>
#include <valarray>;
#include <limits>;

using namespace std;

// 14.2 数学函数
void f1() {
	errno = 0;
	sqrt(-1);
	if (errno == EDOM) {
		cerr << "....";
	}

	errno = 0;
	pow(numeric_limits<double>::max(), 2);
	if (errno == ERANGE) {
		cerr << "....";
	}
}

// 14.3 数值算法

void f3() {
	list<double> lst{ 1,3,5, 9999.999 };
	auto s = accumulate(lst.begin(), lst.end(), 0.0);

	vector<double> v = { 1,3, 5, 999.0 };
	auto s1 = reduce(v.begin(), v.end());

	auto s2 = reduce(execution::par_unseq, v.begin(), v.end());

}

// 14.4 复数
void f4(complex<double> fl, complex<double> db) {
	complex<long double> ld{ fl + sqrt(db) };
}

// 14.5 随机数
class Rand_int {
public:
	Rand_int(int low, int high) : dist{ low,high } {}
	int operator()() { return dist(re); }
	void seed(int s) { re.seed(s); }
private:
	default_random_engine re;
	uniform_int_distribution<> dist;
};
void f5() {
	using my_engine = default_random_engine;
	using my_distribution = uniform_int_distribution<>;

	my_engine re{};
	my_distribution one_to_six{ 1,6 };
	auto die = [&re,one_to_six]() {return one_to_six(re); };

	int x = die();
	Rand_int rnd{ 0, 20 };
	int x1 = rnd();
}

// 14.6 向量算术
void f6(valarray<double>& a1, valarray<double>& a2) {
	valarray<double> a = a1 * 3 + a2 / a1;
	a2 += a1 * 2.1;
	a = abs(a);
}

// 14.7 数值限制
void f7() {
	static_assert(numeric_limits<char>::is_signed, "unsigned char!");
	static_assert(1000000 < numeric_limits<int>::max(), "small ints!");
}