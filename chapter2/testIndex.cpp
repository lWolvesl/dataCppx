//
// Created by wolves on 2022/3/16.
//

#include "iostream"

using namespace std;

void test(int &x) {
    x = 1024;
}

void RunIndex() {
    int x = 1;
    cout << x << endl;
    test(x);
    cout << x << endl;
}