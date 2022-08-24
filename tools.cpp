//
// Created by wolves on 2022/7/19.
//
#pragma once //确保只会引用一次

#include "stdarg.h"
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/**
 * 随机生成数字的种子更改值
 */
int Rand_times = 0;
int Rand_index = -1;
int rands[40];

// 十进制int转char* & string
char *tIntToString(int num)//10进制
{
    //获取长度
    int length = 0;
    int temp = num;
    while (temp != 0) {
        temp = temp / 10;
        length++;
    }

    //分配空间
    char *str = (char *) malloc(sizeof(char) * length);
    int i = 0;//指示填充str
    if (num < 0) {//如果num为负数，将num变正
        num = -num;
        str[i++] = '-';
    }

    //转换
    do {
        str[i++] = num % 10 + 48;//取num最低位 字符0~9的ASCII码是48~57；简单来说数字0+48=48，ASCII码对应字符'0'
        num /= 10;//去掉最低位
    } while (num);//num不为0继续循环

    str[i] = '\0';

    //确定开始调整的位置
    int j = 0;
    if (str[0] == '-') {//如果有负号，负号不用调整
        j = 1;//从第二位开始调整
        ++i;//由于有负号，所以交换的对称轴也要后移1位
    }
    //对称交换
    for (; j < i / 2; j++) {
        //对称交换两端的值 其实就是省下中间变量交换a+b的值：a=a+b;b=a-b;a=a-b;
        str[j] = str[j] + str[i - 1 - j];
        str[i - 1 - j] = str[j] - str[i - 1 - j];
        str[j] = str[j] - str[i - 1 - j];
    }

    return str;//返回转换后的值
}

//换行
void tEnter() {
    printf("\n");
}

char *tGetTimeStr() {
    //获取标准时间
    char *times = (char *) malloc(sizeof(char) * 20);
    time_t timeX;
    struct tm *p;
    time(&timeX);
    p = gmtime(&timeX);

    strcat(times, tIntToString(p->tm_year + 1900));
    strcat(times, "/");

    //拼接字符串
    int mouth = (p->tm_mon + 1) % 12;
    if (mouth < 10) {
        strcat(times, "0");
    }
    strcat(times, tIntToString(mouth));
    strcat(times, "/");

    int day = p->tm_mday;
    if (day < 10) {
        strcat(times, "0");
    }
    strcat(times, tIntToString(day));
    strcat(times, " ");

    int hour = (p->tm_hour + 8) % 24;
    if (hour < 10) {
        strcat(times, "0");
    }
    strcat(times, tIntToString(hour));
    strcat(times, ":");

    int minute = p->tm_min;
    if (minute < 10) {
        strcat(times, "0");
    }
    strcat(times, tIntToString(minute));
    strcat(times, ":");

    int second = p->tm_sec;
    if (second < 10) {
        strcat(times, "0");
    }
    strcat(times, tIntToString(second));

    return times;
}

//打印时间戳
void tPrintTime() {
    char *times = tGetTimeStr();
    strcat(times, " ");
    printf("%s", times);
}

/**
 * 不换行快速打印 string 值
 * @重载方法
 * @param text
 */
void tPrint(const char *text) {
    printf("%s", text);
}

/**
 * 打印info
 */
void tPrintInfo() {
    printf("\033[34minfo \033[0m");
}

/**
 * 打印时间戳和info
 */
void tPrintTimeInfo() {
    tPrintTime();
    tPrintInfo();
}

/**
 * 不换行快速打印 int 值
 * @重载方法
 * @param text
 */
void tPrint(int text) {
    printf("%d", text);
}

/**
 * 快速换行打印 string 值
 * @重载方法
 * @param text
 */
void tPrintln(const char *text) {
    printf("%s\n", text);
}

/**
 * 快速换行打印 int 值
 * @重载方法
 * @param text
 */
void tPrintln(int text) {
    printf("%d\n", text);
}

/**
 * 快速换行打印 int 值
 * @重载方法
 * @param text
 */
void tPrintln(char text) {
    printf("%c\n", text);
}

/**
 * 以log形式打印 string 值
 * @重载方法
 * log模式打印 格式为 year/mouth/day hour:minute:second info xxx
 * @param text
 */
void tLog(const char *text) {
    tPrintTime();
    printf("\033[34minfo \033[0m");
    tPrintln(text);
}

/**
 * 以log形式打印 int 值
 * @重载方法
 * log模式打印 格式为 year/mouth/day hour:minute:second info xxx
 * @param text
 */
void tLog(int text) {
    tPrintTime();
    printf("\033[34minfo \033[0m");
    tPrintln(text);
}

/**
 * 以log形式打印 char 值
 * @重载方法
 * log模式打印 格式为 year/mouth/day hour:minute:second info xxx
 * @param text
 */
void tLog(char text) {
    tPrintTime();
    tPrintInfo();
    tPrintln(text);
}

// 输出一段语句表示程序编译完成以下开始执行
void tStart() {
    tLog("Compile complete!");
}

// 输出一段语句表示程序结束
void tEnd() {
    tLog("done!");
}

// int判断大小
int tMaxInt(int a, int b) {
    return a > b ? a : b;
}

// int判断小
int tMinInt(int a, int b) {
    return a < b ? a : b;
}

// 输出true&false
void tBool(bool tag) {
    if (tag) {
        tPrintln("true");
    } else {
        tPrintln("false");
    }
}

/**
 * @details 由于C/C++的随机数是伪随机，并且运行时在cpu时钟周期改变时rand会重制,因此创建一个长度为40的随机数数组，在调用开始时就确定随机数，保证每次随机生成值尽可能不同
 * @arg 变量Rand_times为全局变量调用次数，确保每次调用结果均不同
 * @author li
 * @return
 */
int getRands() {
    if (Rand_index == -1 || Rand_index == 40) {
        srand((unsigned) time(NULL) + Rand_times);
        Rand_times += 1;
        rands[Rand_index] = rand();
    }
    return rands[Rand_index];
}

/**
 * 生成一个10以内随机的int值
 * @return 随机数
 */
int tRandom10() {
    return getRands() % 10;
}

/**
 * 生成一个100以内随机的int值
 * @return 随机数
 */
int tRandom100() {
    return getRands() % 100;
}

/**
 * 生成一个自定义[x,y]范围以内随机的int值
 * @param start 起始值
 * @param end 终止值
 * @return 随机数
 */
int tRandom(int start, int end) {
    return getRands() % (end - start + 1) + start;
}

/**
 * 单向链表节点
 * @支持泛型 使用方法 tNode<T> *node = tCreateNode<T>(); 使用方法 tNode<T> *node = tCreateNode<T>(value);
 * @tparam T
 */
template<class T>
struct tNode {
    T value;
    struct tNode *next;
};

/**
 * 创建单向链表节点
 * @支持泛型 使用方法 tNode<T> *node = tCreateNode<T>();
 * @return
 */
template<class T>
tNode<T> *tCreateNode() {
    return (tNode<T> *) malloc(sizeof(tNode<T>));
}

/**
 * 创建泛型单向链表节点节点并为value赋值
 * @支持泛型 使用方法 tNode<T> *node = tCreateNode(value);
 * @param data
 * @return
 */
template<class T>
tNode<T> *tCreateNode(T value) {
    tNode<T> *node = (tNode<T> *) malloc(sizeof(tNode<T>));
    node->value = value;
    return node;
}

/**
 * 单向链表实现的栈
 * @支持泛型 使用方法 tStack<T> stack = tCreateStack<T>();
 * @tparam T
 */
template<class T>
struct tStack {
    int size;
    tNode<T> *node;
};

/**
 * 创建栈
 * @支持泛型 使用方法 tStack<T> stack = tCreateStack<T>();
 * @tparam T
 * @return
 */
template<class T>
tStack<T> tCreateStack() {
    tStack<T> stack;
    stack.size = 0;
    return stack;
}

/**
 * 判断栈是否为空
 * @支持泛型
 * @param stack
 * @return
 */
template<class T>
bool empty(tStack<T> &stack) {
    return !stack.size;
}

/**
 * 向栈中插入元素
 * @支持泛型
 * @param stack
 * @param value
 * @return
 */
template<class T>
void push(tStack<T> &stack, T value) {
    tNode<T> *node = tCreateNode(value);
    node->next = stack.node;
    stack.node = node;
    stack.size++;
}

/**
 * 从栈中推出元素
 * @支持泛型
 * @param stack
 * @return
 */
template<class T>
T pop(tStack<T> &stack) {
    tNode<T> *node = stack.node;
    stack.node = node->next;
    T value = node->value;
    free(node);
    stack.size--;
    return value;
}

/**
 * 查看栈顶元素值
 * @支持泛型
 * @param stack
 * @return
 */
template<class T>
T peek(tStack<T> &stack) {
    return stack.node->value;
}

/**
 * 双向链表节点
 * @支持泛型
 */
template<class T>
struct tDNode {
    T value;
    tDNode *next;
    tDNode *prior;
};

/**
 * 双向链表实现的队列
 * 仅允许尾进头出
 * @支持泛型
 * size 为当前队列中有多少元素
 */
template<class T>
struct tQueue {
    int size;
    struct tDNode<T> *head, *tail;
};

/**
 * 双向链表实现的队列
 * 支持头尾双入双出
 * @支持泛型
 * size 为当前队列中有多少元素
 */
template<class T>
struct tDeque {
    int size;
    struct tDNode<T> *head, *tail;
};

/**
 * 创建双向链表节点
 * @支持泛型 使用方法 tDNode<T> *node = tCreateDNode(value);
 * @return
 */
template<class T>
tDNode<T> *tCreateDNode() {
    return (tDNode<T> *) malloc(sizeof(tDNode<T>));
}

/**
 * 创建双向链表节点并为value赋值
 * @支持泛型 使用方法 tDNode<T> *node = tCreateDNode(value);
 * @param value
 * @return
 */
template<class T>
tDNode<T> *tCreateDNode(T value) {
    tDNode<T> *node = (tDNode<T> *) malloc(sizeof(tDNode<T>));
    node->value = value;
    return node;
}

/**
 * 创建队列
 * @支持泛型 使用方法 tQueue<T> queue = tCreateQueue<T>();
 * @tparam T
 * @return
 */
template<class T>
tQueue<T> tCreateQueue() {
    tQueue<T> queue;
    queue.size = 0;
    return queue;
}

/**
 * 判断队列是否为空
 * @支持泛型
 * @param stack
 * @return
 */
template<class T>
bool empty(tQueue<T> &queue) {
    return !queue.size;
}

/**
 * 元素入队(队尾)
 * @支持泛型
 * @tparam T
 * @param queue
 * @param value
 */
template<class T>
void push(tQueue<T> &queue, T value) {
    tDNode<T> *node = tCreateDNode(value);
    if (queue.size == 0) {
        queue.head = node;
    } else {
        node->prior = queue.tail;
        queue.tail->next = node;
    }
    queue.tail = node;
    queue.size++;
}

/**
 * 队首元素出队
 * @支持泛型
 * @tparam T
 * @param queue
 * @return
 */
template<class T>
T pop(tQueue<T> &queue) {
    tDNode<T> *node = queue.head;
    queue.head = node->next;
    T value = node->value;
    delete (node); //free
    queue.size--;
    if (queue.size == 0) {
        queue.tail = queue.head;
    }
    return value;
}

/**
 * 查看队首元素
 * @支持泛型
 * @tparam T
 * @param queue
 * @return
 */
template<class T>
T peek(tQueue<T> &queue) {
    return queue.head->value;
}

template<class T>
T peek_back(tQueue<T> &queue) {
    return queue.tail->value;
}

/**
 * 实现多字符串拼接
 * @param quantity 传入字符串个数
 * @param ... 类型为char*
 * @return
 */
char *tStrCat(int quantity, ...) {
    char *text = (char *) malloc(sizeof(char));
    char *value;
    va_list arg_ptr;
    va_start(arg_ptr, quantity);
    for (int i = 0; i < quantity; i++) {
        value = va_arg(arg_ptr, char *);
        strcat(text, value);
    }
    va_end(arg_ptr);
    return text;
}

/**
 * 创建双端队列
 * @支持泛型 使用方法 tDeque<T> deque = tCreateDeque<T>();
 * @tparam T
 * @return
 */
template<class T>
tDeque<T> tCreateDeque() {
    tDeque<T> deque;
    deque.size = 0;
    return deque;
}

/**
 * 判断双端队列是否为空
 * @支持泛型
 * @param stack
 * @return
 */
template<class T>
bool tEmpty(tDeque<T> &deque) {
    return !deque.size;
}

/**
 * 向双端队列队首插入元素
 * @支持泛型
 * @tparam T
 * @param deque
 * @param value
 */
template<class T>
void tPush_front(tDeque<T> &deque, T value) {
    tDNode<T> *node = tCreateDNode(value);
    if (deque.size == 0) {
        deque.tail = node;
    } else {
        node->next = deque.head;
        deque.head->prior = node;
    }
    deque.head = node;
    deque.size++;
}

/**
 * 向双端队列队尾插入元素
 * @支持泛型
 * @tparam T
 * @param deque
 * @param value
 */
template<class T>
void tPush_back(tDeque<T> &deque, T value) {
    tDNode<T> *node = tCreateDNode(value);
    if (deque.size == 0) {
        deque.head = node;
    } else {
        node->prior = deque.tail;
        deque.tail->next = node;
    }
    deque.tail = node;
    deque.size++;
}

/**
 * 从双端队列队首推出元素
 * @支持泛型
 * @tparam T
 * @param deque
 * @return
 */
template<class T>
T tPop_front(tDeque<T> &deque) {
    tDNode<T> *node = deque.head;
    deque.head = node->next;
    T value = node->value;
    free(node);
    deque.size--;
    if (deque.size == 0) {
        deque.tail = deque.head;
    }
    return value;
}

/**
 * 从双端队列队尾推出元素
 * @tparam T
 * @param deque
 * @return
 */
template<class T>
T tPop_back(tDeque<T> &deque) {
    tDNode<T> *node = deque.tail;
    deque.tail = node->prior;
    T value = node->value;
    free(node);
    deque.size--;
    if (deque.size == 0) {
        deque.head = deque.tail;
    }
    return value;
}

/**
 * 读取双端队列队首元素
 * @支持泛型
 * @tparam T
 * @param deque
 * @return
 */
template<class T>
T tPeek_front(tDeque<T> &deque) {
    return deque.head->value;
}

/**
 * 读取双端队列队尾元素
 * @tparam T
 * @param deque
 * @return
 */
template<class T>
T tPeek_back(tDeque<T> &deque) {
    return deque.tail->value;
}