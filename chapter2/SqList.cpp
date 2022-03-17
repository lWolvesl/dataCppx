//
// Created by wolves on 2022/3/17.
//

#include <cstdlib>
#include <cstdio>

#define iniSize 10;

typedef struct {
    int *data;
    int length;
    int listSize;
} SqList;

void InitSqList(SqList &L) {
    int length = iniSize;
    L.listSize = length;
    L.data = (int *) malloc(length * sizeof(int));
    L.length = 0;
}

void InitSqList(SqList &L, int length) {
    L.listSize = length;
    L.data = (int *) malloc(length * sizeof(int));
    L.length = 0;
}

int Length(SqList &L) {
    return L.length;
}

/**
 * 增加顺序表长度
 * @param L
 * @param length  需要扩充的长度
 */
void IncreaseSize(SqList &L, int length) {
    int *p = L.data;
    L.data = (int *) malloc(sizeof(int) * (L.listSize + length));
    for (int i = 0; i < L.length; ++i) {
        L.data[i] = p[i];
    }
    L.listSize += length;
    free(p);
}

int LocateElem(SqList &L, int e) {
    for (int i = 0; i < L.length; ++i) {
        if (e == L.data[i]) {
            return i;
        }
    }
    return -1;
}

int GetElem(SqList &L, int i) {
    return L.data[i];
}

bool ListInsert(SqList &L, int i, int e) {
    if (L.length == L.listSize) {
        return false;
    }
    for (int j = L.length; j > i; j--) {
        L.data[j] = L.data[j - 1];
    }
    L.data[i] = e;
    L.length++;
    return true;
}

bool ListDelete(SqList &L, int i, int &e) {
    if (L.length == 0 || i >= L.length) {
        return false;
    }
    e = L.data[i];
    for (int j = i; j < L.length; ++j) {
        L.data[j] = L.data[j + 1];
    }
    L.length--;
    return true;
}

void PrintList(SqList &L) {
    for (int i = 0; i < L.length; ++i) {
        printf("%d  ", L.data[i]);
    }
}

bool Empty(SqList &L) {
    return L.length == 0;
}

void DestroyList(SqList &L) {
    free(L.data);
    L.length = 0;
}

