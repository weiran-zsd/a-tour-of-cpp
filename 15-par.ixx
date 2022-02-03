#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <condition_variable>
#include <queue>
#include <future>
#include <cmath>;
#include <numeric>

export module _15_par;

using namespace std;
// 15.2 task & thread
void f() { cout << "hello"s; };
struct F {
	void operator()() { cout << "world"s; };
};

void f2() {
	thread t1{ f };
	thread t2{ F() };
	t1.join(); // 等待t1完成
	t2.join(); // 等待t2完成
}


// 15.3 传递参数
void _f3(vector<double>& v) {}
struct _F {
	vector<double>& v;
	_F(vector<double>& vv):v{vv} {}
	void operator()(){}
};

void f3() {
	vector<double> v1{ 1,3,5,7,9 };
	vector<double> v2{ 11,12,1,5 };

	thread t1{ _f3, ref(v1) };
	thread t2{ _F(v2)};
}

// 15.4 返回结果
void _f4(vector<double>& v, double* res){}
class _F4 {
public:
	_F4(vector<double>& vv, double* p) :v{ vv }, res{ p } {}
	void operator()(){}
private:
	vector<double>& v;
	double* res;
};

double g(vector<double>&);

void f4(vector<double>& v1, vector<double>& v2, vector<double>& v3) {
	double res1;
	double res2;
	double res3;

	thread t1{ _f4, ref(v1),&res1 };
	thread t2{ _F4{v2, &res2} };
	thread t3{ [&]() {res3 = g(v3); } };

	t1.join();
	t2.join();
	t3.join();

	cout << res1 << res2 << res3;
}

// 15.5 共享数据
mutex m; // 控制访问
int sh; // 共享数据

void f5() {
	scoped_lock lck{ m }; // => m.lock()
	sh += 7;

	// 隐式释放 mutex; => m.unlock();
}


shared_mutex mx;
void reader() {
	shared_lock lck{ mx };
	//read...
}

void writer() {
	unique_lock lck{ mx };
	//write...
}

// 15.6 等待事件
using namespace chrono;
void f6() {
	auto t0 = high_resolution_clock::now();
	this_thread::sleep_for(milliseconds{ 20 });
	auto t1 = high_resolution_clock::now();

	cout << duration_cast<nanoseconds>(t1 - t0).count() << "ns passed.";
}

class Message {
	//...
};

queue<Message> mqueue;
condition_variable mcond;
mutex mmutex;

void consumer() {
	while (true) {
		unique_lock lck{ mmutex };
		mcond.wait(lck, [] {return !mqueue.empty(); });

		auto m = mqueue.front();
		mqueue.pop();
		lck.unlock();
	}
}

void producer() {
	while (true) {
		Message m;
		scoped_lock lck{ mmutex };
		mqueue.push(m);
		mcond.notify_one();
	}
}


// 15.7 任务通信
struct X{};
void f7(promise<X>& px) {
	try {
		X res;
		px.set_value(res);
	}
	catch (...) {
		px.set_exception(current_exception());
	}
}

void g7(future<X>& fx) {
	X v = fx.get();
}

// packaged_task

double accum(double* beg, double* end, double init) {
	return accumulate(beg, end, init);
}

double comp2(vector<double>& v) {
	using Task_type = double(double*, double*, double);
	packaged_task<Task_type> pt0{ accum };
	packaged_task<Task_type> pt1{ accum };

	future<double> f0{ pt0.get_future() };
	future<double> f1{ pt1.get_future() };

	double* first = &v[0];
	thread t1{ move(pt0), first, first + v.size() / 2, 0 };
	thread t2{ move(pt1), first + v.size() / 2, first + v.size(), 0 };

	//...
	return f0.get() + f1.get();
}

// async
double comp4(vector<double>& v) {
	if (v.size() < 1000) {
		return accumulate(v.begin(), v.end(), 0.0);
	}

	auto v0 = &v[0];
	auto sz = v.size();
	

	auto f0 = async(accum, v0 + sz * 0/4, v0 + sz * 1/4, 0.0);
	auto f1 = async(accum, v0 + sz * 1/4, v0 + sz * 1/2, 0.0);
	auto f2 = async(accum, v0 + sz * 2/4, v0 + sz * 3/4, 0.0);
	auto f3 = async(accum, v0 + sz * 3/4, v0 + sz * 4/4, 0.0);

	return f0.get() + f1.get() + f2.get() + f3.get();
	
}