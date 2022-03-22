//
// Created by wolves on 2022/3/18.
// 😚
//
#include "SqList.cpp"
#include "iostream"

using namespace std;

bool exercises1(SqList &L) {
    if (L.length == 0) {
        return false;
    }
    int min = 0;
    for (int i = 1; i < L.length; ++i) {
        if (L.data[min] > L.data[i]) {
            min = i;
        }
    }
    L.data[min] = L.data[L.length - 1];
    L.length--;
    return true;
}

void exercises2(SqList &L) {
    for (int i = 0; i < L.length / 2; ++i) {
        int temp = L.data[i];
        L.data[i] = L.data[L.length - 1 - i];
        L.data[L.length - 1 - i] = temp;
    }
}

void exercises3(SqList &L, int e) {
    int m;
    for (int i = 0; i < L.length; ++i) {
        if (e == L.data[i]) {
            ListDelete(L, i + 1, m);
        }
    }
}

bool exercises4(SqList &L, int s, int t) {
    if (s > t || L.length == 0) {
        return false;
    }
    int temp = t - s + 1;
    for (int i = t - 1; i < L.length - temp; ++i) {
        L.data[i] = L.data[i + temp];
    }
    L.length -= temp;
    return true;
}

void exercises5(SqList &L) {
    int temp = L.data[L.length - 1];
    int e;
    for (int i = L.length - 2; i >= 1; --i) {
        if (temp == L.data[i]) {
            ListDelete(L, i, e);
        } else {
            temp = L.data[i];
        }
    }
}

SqList exercises7(SqList &L1, SqList &L2) {
    SqList L3;
    int length = L1.length + L2.length;
    L3.data = (int *) malloc(length * sizeof(int));
    L3.listSize = L1.listSize + L2.listSize;
    L3.length = length;
    int m = 0;
    for (int i = 0; i < L1.length; ++i) {
        L3.data[m] = L1.data[i];
        m++;
    }
    for (int i = 0; i < L2.length; ++i) {
        L3.data[m] = L2.data[i];
        m++;
    }
    free(L1.data);
    free(L2.data);
    return L3;
}

void exercises8(SqList &L, int m, int n) {
    int *p = (int *) malloc(m * sizeof(int));
    for (int i = 0; i < m; ++i) {
        p[i] = L.data[m+i];
        L.data[m+i];
    }

}

/**
 * 测试单元
 */
void testExercises1() {
    SqList L = createListOne();
    exercises1(L);
    PrintList(L);
}

void testExercises2() {
    SqList L = createListOne();
    ListAppend(L, 3);
    exercises2(L);
    PrintList(L);
}

void testExercises3() {
    SqList L = createListOne();
    exercises3(L, 2);
    PrintList(L);
}

void testExercises4x5() {
    SqList L = createListOne();
    printf("%d\n", exercises4(L, 4, 5));
    PrintList(L);
}

void testExercise6() {
    SqList L;
    InitSqList(L, 6);
    L.data[0] = 1;
    L.data[1] = 1;
    L.data[2] = 2;
    L.data[3] = 3;
    L.data[4] = 3;
    L.data[5] = 3;
    L.length = 6;
    exercises5(L);
    PrintList(L);
}

void testExercise7() {
    SqList L1 = createListOne();
    SqList L2 = createListOne();
    SqList L3 = exercises7(L1, L2);
    PrintList(L3);
}

void testExercises8() {
    SqList L = createListOne();
    exercises8(L, 4, 5);
    printf("\n");
    PrintList(L);
}

void testList2_2() {
    //testExercises1();
    //testExercises2();
    //testExercises3();
    //testExercises4x5();
    //testExercise6();
    //testExercise7();
    testExercises8();
}
