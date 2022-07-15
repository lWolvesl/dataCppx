//
// Created by wolves on 2022/4/8.
//

#include "iostream"

using namespace std;

int *get_next(string T) {
    int *next = (int *) malloc(sizeof(int) * (T.length() + 1));
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length()) {
        if (j == 0 || T[i] == T[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
    return next;
}

void test() {
    string T = "ababaaababaa";
    int *next = get_next(T);
    for (int i = 0; i < T.length() + 1; ++i) {
        cout << next[i]<<" ";
    }
    free(next);
}