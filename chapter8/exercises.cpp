//
// Created by wolves on 2022/11/12.
// 第八章习题（仅408真题）
//

#include "../tools.cpp"

/**
 * 8.3.4 第七题 2016年统考真题
 * @param array
 * @param length
 * @return
 */
int exercise1(int *array, int length) {
    int temp, low = 0, high = length - 1, low0 = 0, high0 = length - 1, flag = 1, k = length / 2, i;
    int s1 = 0, s2 = 0;
    while (flag) {
        temp = array[low];
        while (low < high) {
            while (low < high && array[high] >= temp) {
                high--;
            }
            array[low] = array[high];
            while (low < high && array[low] <= temp) {
                low++;
            }
            array[high] = array[low];
        }
        array[low] = temp;
        if (low == k - 1) {
            flag = 0;
        } else {
            if (low < k - 1) {
                low0 = ++low;
                high = high0;
            } else {
                high0 = --high;
                low = low0;
            }
        }
    }
    for (i = 0; i < k; ++i) {
        s1 += array[i];
    }
    for (i = k + 1; i < length; ++i) {
        s2 += array[i];
    }
    return s2 - s1;
}