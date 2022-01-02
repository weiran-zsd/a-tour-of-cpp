#include<iostream>
#include <complex>
#include <vector>
#include <list>

export module _01_basic;

using namespace std;

double square(double x) {
    return x * x;
}

void print_square(double x) {
    cout << "the square of " << x << " is " << square(x) << "\n";
}

// 1.4.2 ��ʼ��
double d1 = 2.3;
double d2{ 2.3 };
double d3 = { 2.3 };
complex<double> z = 1;
complex<double> z2{ d1, d2 };
complex<double> z3 = { d1, d2 };

vector<int> v{ 1,3 };

// 1.5 ���������������
struct Record {
    string name;
};

void fct(int arg) {
    string motto{ "who dare wins" };
    auto p = new Record{ "Hume" };
}


// 1.6����
constexpr int dmw = 17; // �����ɱ���������
int var = 17;
const double sqv = sqrt(var);

double sum(vector<double>& v) {
    double res = 0;
    for (auto x : v) { res += x; }
    return res;
};

vector<double> vd{ 1.2, 1.3, 1.4 };
const double s1 = sum(vd);
//constexpr double s2 = sum(vd); // sum(vd)���ǳ������ʽ

constexpr double csquare(double x) { return x * x; }
constexpr double max1 = 1.4 * csquare(17);
//constexpr double max2 = 1.4 * csquare(var); // var���ǳ������ʽ
const double max3 = 1.4 * square(var);

constexpr double nth(double x, int n) {
    double res = 1;
    int i = 0;
    while (i < n) {
        res *= x;
        ++i;
    }
    return res;
}

// 1.7 ָ�롢���顢����

char vs[6] = {'a', 'b'};
char* p = &vs[3];

void copy_fct() {
    int v1[10] = { 0,1,2,3,4,5,6,7,8,9, };
    int v2[10];

    for (auto i = 0; i != 10; i++) {
        v2[i] = v1[i];
    }
}

void print() {
    int v[] = { 0,1,2,3,4,5,6,7,8,9, };
    for (auto x : v) {
        cout << x << "\n";
    }

    for (auto x : { 10, 20, 30 }) {
        cout << x << "\n";
    }
}

void increment() {
    int v[] = { 0,1,2,3,4,5,6,7,8,9, };
    for (auto& x : v) {
        x++;
    }
}

void sort(vector<double>& v) {
    string a[10];
    string* p;
    string s;
    string& r = s;
    string f(string);

    double* pd = nullptr;
    list<Record>* lst = nullptr;
}

// ͳ��x�� p[]���ֵĴ���
int count_x(const char* p, char x) {
    if (p == nullptr) {
        return 0;
    }
    int count = 0;
    for (; *p != 0; p++) {
        if (*p == x) {
            count++;
        }
    }
    return count;
}

// 1.9 ����
bool accept() {
    cout << "proceed?\n";
    char answer = 0;
    cin >> answer;

    return answer == 'y';
}

bool accept2() {
    cout << "proceed?\n";
    char answer = 0;
    cin >> answer;

    switch (answer) {
    case 'y': return true;
    case 'n': return false;
    default:
        cout << "I'll take that for a no.\n";
        return false;
    }
}
struct Point {
    double x = 0;
    double y = 0;
};
void action() {
    while (true) {
        cout << "enter action:\n";
        string act;
        cin >> act;
        Point delta{ 0, 0 };

        for (char ch : act) {
            switch (ch) {
            case 'u': // ��
            case 'n': // ��
                delta.y++;
                break;
            case 'r': // ��
            case 'e':
                delta.x++;
                break;
            //...
            default:
                cout << "I freeze!\n";
            }
        }
    }
}

// 1.9.1 ��ֵ
void assign() {
    int x = 0;
    int y = 1;
    x = y;

    int* p = &x;
    int* q = &y;
    p = q;

    int& r = x;
    int& r2 = y;
    r = r2;
}

// 1.9.2 ��ʼ��
void init() {
    int x = 7;
    int& r{ x };
    r = 7;
}
