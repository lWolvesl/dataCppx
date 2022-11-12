//
// Created by wolves on 2022/11/12.
//
#include "../tools.cpp"

//排序算法所用的结构体，可选用
typedef struct {
    int *value;         //int型数组
    int length;         //当前数组长度
    int size;           //数组可容纳最大值
} Array;

Array ArrayInit(int size) {
    Array array;
    array.size = size;
    array.value = (int *) malloc(array.size * sizeof(int));
    return array;
}

void ArrayRandom(Array *array, int length) {
    array->length = length;
    for (int i = 0; i < length; ++i) {
        array->value[i] = tRandom100();
    }
}

/**
 * 创建一个指针数组并随机放置小于100的整数，若需要将0号位设置为哨兵/暂存，请使用本函数时将 length+1
 * @param length
 * @return
 */
int *CreateArray(int length) {
    int *array = (int *) malloc(length * sizeof(int));
    for (int i = 0; i < length; ++i) {
        array[i] = tRandom100();
    }
    return array;
}

int *CopyArray(int *array, int length) {
    int *copy = (int *) malloc(length * sizeof(int));
    for (int i = 0; i < length; ++i) {
        copy[i] = array[i];
    }
    return copy;
}

void PrintArray(int *array, int length) {
    tPrintTimeInfo();
    tPrint("array:[");
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            tPrint(",");
        }
        tPrint(array[i]);
    }
    tPrint("]\n");
}

void PrintArray(int *array, int length, const char *text) {
    tPrintTimeInfo();
    tPrint(text);
    tPrint("array:[");
    for (int i = 0; i < length; ++i) {
        if (i != 0) {
            tPrint(",");
        }
        tPrint(array[i]);
    }
    tPrint("]\n");
}