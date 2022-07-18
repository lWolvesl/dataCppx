//
// Created by wolves on 2022/4/8.
//
#include "HString.cpp"

int *get_next(HString T) {
    int *next = (int *) malloc(sizeof(int) * (T.length + 1));
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
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
    HString T = createStr("ababaaababaa");
    int *next = get_next(T);
    for (int i = 0; i < T.length + 1; ++i) {
        printf("%d ", next[i]);
    }
    free(next);
}