// a-tour-of-cpp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

import _03_module;
#include<cmath>
#include <iostream>

double sqrt_sum(Vector& v) {
    double sum = 0;
    for (int i = 0; i != v.size(); i++) {
        sum += std::sqrt(v[i]);
    }

    return sum;
}

int main()
{

    std::cout << "hello world!\n";
    return 0;
}
