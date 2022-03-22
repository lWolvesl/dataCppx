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

/**
 * 第六题
 * @param L1
 * @param L2
 */
void exercises6(SqList &L) {
    if (L.length == 1) {
        return;
    }
    int index = 0;
    int compare = 1;
    while (compare < L.length) {
        if (L.data[index] != L.data[compare]) {
            index = compare;
            compare++;
            continue;
        }
        for (int i = compare; i < L.length - 1; ++i) {
            L.data[i] = L.data[i + 1];
        }
        L.length--;
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
    for (int i = 0; i < n; ++i) {
        p[i] = L.data[m + i];
    }
    for (int i = m - 1, end = L.length - 1; i >= 0; --i, --end) {
        L.data[end] = L.data[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        L.data[i] = p[i];
    }
}

/**
 * 第九题
 * 有序，找x
 */
int assist9(SqList &L, int start, int end, int x) {
    int index = (start + end) / 2;
    if (L.data[index] == x) {
        printf("%d\n", index);
        return index;
    }
    if (start == end) {
        return -1;
    }
    return assist9(L, L.data[(start + end) / 2] > x ? start : (start + end) / 2 / 2,
                   (L.data[(start + end) / 2] > x ? (start + end) / 2 / 2
                                                  : end) - 1, x);
}

void exercises9(SqList &L, int x) {
    int index = L.data[L.length / 2] == x ? L.length / 2 : assist9(L, L.data[L.length / 2] > x ? 0 : L.length / 2,
                                                                   (L.data[L.length / 2] > x ? L.length / 2
                                                                                             : L.length) - 1, x);
    if (index != -1) {
        if (index == L.length - 1) {
            return;
        }
        int temp = L.data[index];
        L.data[index] = L.data[index + 1];
        L.data[index + 1] = temp;
        return;
    }
    ++index;
    while (L.data[index] < x && index < L.length) {
        index++;
    }
    int *p = (int *) malloc(sizeof(int) * (L.length + 1));
    L.length++;
    for (int i = 0; i < index; ++i) {
        p[i] = L.data[i];
    }
    p[index] = x;
    for (int i = index + 1; i < L.length; ++i) {
        p[i] = L.data[i + 1];
    }

    free(L.data);
    L.data = p;
}

/**
 * 循环移动
 * 空间复杂度S(p) 时间复杂度O(n)
 */
void exercises10(SqList &L, int q) {
    if (q == L.length) {
        return;
    }
    int *p = (int *) malloc(sizeof(int) * q);
    for (int i = 0; i < q; ++i) {
        p[i] = L.data[i];
    }
    for (int i = 0; i < L.length - q; ++i) {
        L.data[i] = L.data[i + q];
    }
    for (int i = 0; i < q; ++i) {
        L.data[i + L.length - q] = p[i];
    }
}

/**
 * 11
 * 空间复杂度S(1),时间复杂度S(L)
 * @param L1
 * @param L2
 * @return
 */
int exercises11(SqList &L1, SqList &L2) {
    int index = 0, l1 = 0, l2 = 0, temp;
    for (int i = 0; i < L1.length * 2; ++i) {
        if (L1.data[l1]>=L2.data[l2]){
            temp = L2.data[l2];
            l2++;
        }else{
            temp = L1.data[l1];
            l1++;
        }
        if (++index == L1.length) {
            return temp;
        }
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
    printf("%d", exercises4(L, 4, 5));
    PrintList(L);
}

void testExercise6() {
    SqList L;
    InitSqList(L, 7);
    L.data[0] = 1;
    L.data[1] = 1;
    L.data[2] = 2;
    L.data[3] = 3;
    L.data[4] = 3;
    L.data[5] = 3;
    L.data[6] = 4;
    L.length = 7;
    exercises6(L);
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
    exercises8(L, 5, 4);
    printf("\n");
    PrintList(L);
}

void testExercises9() {
    SqList L;
    InitSqList(L, 7);
    L.data[0] = 1;
    L.data[1] = 1;
    L.data[2] = 2;
    L.data[3] = 3;
    L.data[4] = 3;
    L.data[5] = 3;
    L.data[6] = 4;
    L.length = 7;
    PrintList(L);
    exercises9(L, 5);
    printf("\n");
    PrintList(L);
}

void testExercises10() {
    SqList L = createListOne();
    exercises10(L, 4);
    printf("\n");
    PrintList(L);
}

void testExercises11(){
    SqList L1;
    InitSqList(L1, 7);
    L1.data[0] = 1;
    L1.data[1] = 1;
    L1.data[2] = 2;
    L1.data[3] = 3;
    L1.data[4] = 3;
    L1.data[5] = 4;
    L1.data[6] = 5;
    L1.length = 7;
    SqList L2;
    InitSqList(L2, 7);
    L2.data[0] = 3;
    L2.data[1] = 4;
    L2.data[2] = 5;
    L2.data[3] = 6;
    L2.data[4] = 7;
    L2.data[5] = 8;
    L2.data[6] = 9;
    L2.length = 7;
    PrintList(L1);
    PrintList(L2);
    printf("%d\n",exercises11(L1,L2));
}

void testList2_2() {
    //testExercises1();
    //testExercises2();
    //testExercises3();
    //testExercises4x5();
    //testExercise6();
    //testExercise7();
    //testExercises8();
    //testExercises9();
    //testExercises10();
    testExercises11();
}
