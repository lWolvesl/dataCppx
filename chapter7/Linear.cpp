//
// Created by wolves on 2022/11/1.
//
#include "../tools.cpp"

// 线性结构基础查找算法

typedef struct {
    int *elem;
    int TableLen;
} SSTable, SeqList;

/**
 * 预留哨兵位的有序数组，长度为10/11
 * [7,10,13,14,16,18,25,42,55,60]
 * @return
 */
SSTable getSSTable() {
    SSTable table;
    table.elem = (int *) malloc(sizeof(int) * 11);
    table.elem[1] = 7;
    table.elem[2] = 10;
    table.elem[3] = 13;
    table.elem[4] = 14;
    table.elem[5] = 16;
    table.elem[6] = 18;
    table.elem[7] = 25;
    table.elem[8] = 42;
    table.elem[9] = 55;
    table.elem[10] = 60;
    table.TableLen = 11;
    return table;
}

/**
 * 顺序查找，ASL(成功) = (n + 1) / 2 , ASL(失败) = n + 1
 * @param table
 * @param key
 * @return
 */
int Search_Seq(SSTable table, int key) {
    table.elem[0] = key;
    int i;
    for (i = table.TableLen - 1; table.elem[i] != key; --i);
    return i;
}

void test1() {
    tLog(Search_Seq(getSSTable(), 16));
}

/**
 * 有序数组,长度为10
 * [6,7,10,13,14,16,18,25,42,55]
 * @return
 */
SeqList getSeq() {
    SeqList table;
    table.elem = (int *) malloc(sizeof(int) * 11);
    table.elem[0] = 6;
    table.elem[1] = 7;
    table.elem[2] = 10;
    table.elem[3] = 13;
    table.elem[4] = 14;
    table.elem[5] = 16;
    table.elem[6] = 18;
    table.elem[7] = 25;
    table.elem[8] = 42;
    table.elem[9] = 55;
    table.TableLen = 10;
    return table;
}

/**
 * 折半查找，ASL = log₂(n + 1) - 1
 * @param L
 * @param key
 * @return
 */
int Binary_Search(SeqList L, int key) {
    int low = 0, high = L.TableLen - 1, mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (L.elem[mid] == key) {
            return mid;
        }
        if (L.elem[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void test2(){
    tLog(Binary_Search(getSeq(),17));
}



void run() {
    test2();
}