//
// Created by wolves on 2022/11/12.
// 排序算法
//

#include "./Array.cpp"

/**
 * 插入排序
 * @param array  插入排序所需排序的数组,使用指针数组以达到对原数组进行操作
 * @param length 所需排序数组的长度
 */
void InsertSort(int *array, int length) {
    int i, j, temp;
    for (i = 1; i < length; i++) {
        if (array[i] < array[i - 1]) {
            temp = array[i];
            for (j = i - 1; j >= 0 && array[j] > temp; --j) {
                array[j + 1] = array[j];
            }
            array[j + 1] = temp;
        }
    }
}

void testInsertSort() {
    int *array = CreateArray(10);
    tLog("插入排序");
    PrintArray(array, 10, "排序前 ");
    InsertSort(array, 10);
    PrintArray(array, 10, "排序后 ");
}

/**
 * 折半插入排序
 * @param array
 * @param length
 */
void HalfInsertSort(int *array, int length) {
    int i, j, low, mid, high;
    for (i = 2; i <= length; ++i) {
        array[0] = array[i];                       //0号位暂存
        low = 1;
        high = i - 1;
        while (low <= high) {
            mid = (low + high) / 2;
            if (array[mid] > array[0]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        for (j = i - 1; j >= high + 1; --j) {
            array[j + 1] = array[j];
        }
        array[high + 1] = array[0];
    }
}

void testHalfInsertSort() {
    int *array = CreateArray(11);
    tLog("折半插入排序");
    PrintArray(array, 11, "排序前 ");
    HalfInsertSort(array, 10);
    PrintArray(array, 11, "排序后 ");
    tLog("此处0号位为暂存位，排序后应从1号位置开始看");
}

/**
 * 希尔排序
 * @param array
 * @param length
 */
void ShellSort(int *array, int length) {
    int i, j;
    for (int dk = length / 2; dk >= 1; dk = dk / 2) {
        for (i = dk + 1; i <= length; ++i) {
            if (array[i] < array[i - dk]) {
                array[0] = array[i];                                            //0号位暂存
                for (j = i - dk; j > 0 && array[0] < array[j]; j -= dk) {
                    array[j + dk] = array[j];
                }
                array[j + dk] = array[0];
            }
        }
    }
}

void testShellSort() {
    int *array = CreateArray(11);
    tLog("希尔排序");
    PrintArray(array, 11, "排序前 ");
    ShellSort(array, 10);
    PrintArray(array, 11, "排序后 ");
    tLog("此处0号位为暂存位，排序后应从1号位置开始看");
}

/**
 * 冒泡排序
 * @param array
 * @param length
 */
void BubbleSort(int *array, int length) {
    for (int i = 0; i < length - 1; ++i) {
        bool flag = false;                          //快速判是否有序
        for (int j = length - 1; j > i; --j) {
            if (array[j - 1] > array[j]) {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
                flag = true;
            }
        }
        if (!flag) {
            return;
        }
    }
}

void testBubbleSort() {
    int *array = CreateArray(10);
    tLog("冒泡排序");
    PrintArray(array, 10, "排序前 ");
    BubbleSort(array, 10);
    PrintArray(array, 10, "排序后 ");
}

/**
 * 快速排序确定分组函数
 * @param array
 * @param low
 * @param high
 * @return
 */
int Partition(int *array, int low, int high) {
    int temp = array[low];
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
    return low;
}


/**
 * 快速排序
 * @param array
 * @param length
 * @param low
 * @param high
 */
void QuickSort(int *array, int low, int high) {
    if (low < high) {
        int index = Partition(array, low, high);
        QuickSort(array, low, index - 1);
        QuickSort(array, index + 1, high);
    }
}

void testQuickSort() {
    int *array = CreateArray(100);
    tLog("冒泡排序");
    PrintArray(array, 100, "排序前 ");
    QuickSort(array, 0, 99);
    PrintArray(array, 100, "排序后 ");
}

/**
 * 简单选择排序
 * @param array
 * @param length
 */
void SelectSort(int *array, int length) {
    int min, temp;
    for (int i = 0; i < length - 1; ++i) {
        min = i;
        for (int j = i + 1; j < length; ++j) {
            if (array[min] > array[j]) {
                min = j;
            }
        }
        temp = array[min];
        array[min] = array[i];
        array[i] = temp;
    }
}

void testSelectSort() {
    int *array = CreateArray(10);
    tLog("冒泡排序");
    PrintArray(array, 10, "排序前 ");
    SelectSort(array, 10);
    PrintArray(array, 10, "排序后 ");
}

/**
 * 堆排序
 *    大根堆
 *
 *    计算：
 * @param array
 * @param root
 * @param length
 */
void HeadAdjust(int *array, int root, int length) {

}

void test() {
    testSelectSort();
}