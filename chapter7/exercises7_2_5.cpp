//
// Created by wolves on 2022/11/3.
//
#include "../tools.cpp"

/**
 * 第六题，使用递归实现折半查找
 * @param table
 * @param key
 * @param low
 * @param high
 * @return
 */
int exercises6(int *table, int key, int low, int high) {
    int mid = (low + high) / 2;
    if (low > high) {
        return -1;
    }
    if (table[mid] == key) {
        return mid;
    }
    if (table[mid] > key) {
        return exercises6(table, key, low, mid - 1);
    } else {
        return exercises6(table, key, mid + 1, high);
    }
}

//测速第六题
void test6() {
    int *table = (int *) malloc(sizeof(int) * 10);
    table[0] = 6;
    table[1] = 7;
    table[2] = 10;
    table[3] = 13;
    table[4] = 14;
    table[5] = 16;
    table[6] = 18;
    table[7] = 25;
    table[8] = 42;
    table[9] = 55;
    int index = exercises6(table, 55, 0, 9);
    tLog(index);
}

/**
 * 第七题，根据题目描述，实际构建了一个动态的热查找算法
 *  对于顺序结构来说，①可以使用顺序查找，找到后直接与前一个位置的值互换即可，实现方法简单，不予实现
 *                ②可以使用折半查找，即数组第一次进入时为此数组完成判断树构建，在后续查找时若发现节点，则与其父节点交换，实际操作时无需
 *                      构建二叉树，只需要在查找时记录上一个mid，找到后在数组中交换即可。
 *  对于链式结构来说，使用折半查找会严重降低查找性能，因此需要使用顺序查找，找到后直接与前一个位置的值互换即可，即链表互换位置。
 */

/**
 * 7.对于顺序结构的折半热查找实现
 * @param table 由于此处使用了指针传递数组，因此在方法中修改数组内部数据时会直接修改到原数组，实现查找。
 * @param key   所需要查找的值
 * @param len   原数组长度
 * @return
 */
int exercises7_1(int *table, int key, int len) {
    int count = 0;                        //此处记录每次查找数组时对比数据的次数，方便查看效果
    int last;                             //此处缓存上次的mid
    int low = 0, high = len - 1, mid = (low + high) / 2;
    while (low <= high) {
        last = mid;
        mid = (low + high) / 2;
        count++;
        if (table[mid] == key) {
            //此处进行交换
            int temp = table[mid];
            table[mid] = table[last];
            table[last] = temp;
            tLog(table[last]);

            tPrintTimeInfo();
            tPrint("对比了 ");
            tPrint(count);
            tPrint(" 次\n");
            return mid;
        }
        if (table[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

//测速第七题方法一
void test7_1() {
    int *table = (int *) malloc(sizeof(int) * 10);
    table[0] = 6;
    table[1] = 7;
    table[2] = 10;
    table[3] = 13;
    table[4] = 14;
    table[5] = 16;
    table[6] = 18;
    table[7] = 25;
    table[8] = 42;
    table[9] = 55;
    exercises7_1(table, 18, 10);
    exercises7_1(table, 18, 10);
    exercises7_1(table, 18, 10);
    exercises7_1(table, 18, 10);
}

// 第七题所用数据结构,链表节点
struct x_7_Node {
    int value;
    x_7_Node *next;
};

/**
 * 创建节点并赋值
 * @param value
 * @return
 */
x_7_Node *createNew(int value) {
    x_7_Node *node;
    node = (x_7_Node *) malloc(sizeof(x_7_Node));
    node->value = value;
    return node;
}

/**
 * 第七题所用链表结构的热查找算法实现
 * @param head
 * @param key
 * @param len
 * @return
 */
int exercises7_2(x_7_Node *head, int key, int len) {
    int count = 1;
    x_7_Node *pear, *node;
    node = head;
    while (node && node->value != key) {        //对链表数据查值，若不通则查看下一个
        pear = node;                            //此处记录上一个节点，以便后续交换值
        count++;
        node = node->next;
    }
    if (count > len) {                          //此处判断是否未找到值
        return -1;
    }

    //此处与前一个节点交换值，实现热更新
    int temp = pear->value;
    pear->value = node->value;
    node->value = temp;

    //此处打印每次查找数组时对比数据的次数，方便查看效果
    tPrintTimeInfo();
    tPrint("对比了 ");
    tPrint(count);
    tPrint(" 次\n");
    return count;
}

//测试第七题方法2
void test7_2() {
    x_7_Node *node = createNew(6);
    x_7_Node *head = node;
    node->next = createNew(7);
    node = node->next;
    node->next = createNew(10);
    node = node->next;
    node->next = createNew(13);
    node = node->next;
    node->next = createNew(14);
    node = node->next;
    node->next = createNew(16);
    node = node->next;
    node->next = createNew(18);
    node = node->next;
    node->next = createNew(25);
    node = node->next;
    node->next = createNew(42);
    node = node->next;
    node->next = createNew(55);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
    exercises7_2(head, 18, 10);
}

void run() {
    test7_2();
}