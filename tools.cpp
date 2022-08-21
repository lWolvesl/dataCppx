//
// Created by wolves on 2022/7/19.
//
#pragma once //确保只会引用一次

#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

/**
 * 随机生成数字的种子更改值
 */
int Rand_times = 0;

/**
 * 单向链表节点
 * 节点值为int
 */
struct tNodeI {
    int value;
    struct tNodeI *next;
};

/**
 * 双向链表节点
 * 节点值为int
 */
struct tDNodeI {
    int value;
    tDNodeI *next;
    tDNodeI *prior;
};

/**
 * 链表实现的栈
 * 结构体中的node相当于单向链表头指针
 * 节点值为int
 * size 为当前栈有多少个元素
 */
struct tStackI {
    int size;
    struct tNodeI *node;
};

/**
 * 双向链表实现的队列
 * 仅允许尾进头出
 * 节点值为int
 * size 为当前队列中有多少元素
 */
struct tQueueI {
    int size;
    struct tDNodeI *head, *tail;
};

/**
 * 双向链表实现的队列
 * 仅允许尾进头出
 * 节点值为int
 * size 为当前队列中有多少元素
 */
struct tDequeI {
    int size;
    struct tDNodeI *head, *tail;
};

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
void tPrint(char *text) {
    printf("%s", text);
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
void tPrintln(char *text) {
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
 * 以log形式打印 string 值
 * @重载方法
 * log模式打印 格式为 year/mouth/day hour:minute:second info xxx
 * @param text
 */
void tLog(char *text) {
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
 * 生成一个10以内随机的int值
 * 变量Rand_times为全局变量调用次数，确保每次调用结果均不同
 * @return 随机数
 */
int tRandom10() {
    srand((unsigned) time(NULL) + Rand_times);
    Rand_times++;
    return rand() % 10;
}

/**
 * 生成一个100以内随机的int值
 * 变量Rand_times为全局变量调用次数，确保每次调用结果均不同
 * @return 随机数
 */
int tRandom100() {
    srand((unsigned) time(NULL) + Rand_times);
    Rand_times++;
    return rand() % 100;
}

/**
 * 生成一个自定义[x,y]范围以内随机的int值
 * 变量Rand_times为全局变量调用次数，确保每次调用结果均不同
 * @param start 起始值
 * @param end 终止值
 * @return 随机数
 */
int tRandom(int start, int end) {
    srand((unsigned) time(NULL) + Rand_times);
    Rand_times++;
    return rand() % (end - start + 1) + start;
}

/**
 * 创建单向链表节点
 * @重载函数
 * @return
 */
tNodeI *tCreateNodeI() {
    return (tNodeI *) malloc(sizeof(tNodeI));
}

/**
 * 创建单向链表节点节点并为value赋值
 * @重载函数
 * @param data
 * @return
 */
tNodeI *tCreateNodeI(int value) {
    tNodeI *node = (tNodeI *) malloc(sizeof(tNodeI));
    node->value = value;
    return node;
}

/**
 * 创建双向链表节点
 * @重载函数
 * @return
 */
tDNodeI *tCreateDNodeI() {
    return (tDNodeI *) malloc(sizeof(tDNodeI));
}

/**
 * 创建双向链表节点并为value赋值
 * @重载函数
 * @param value
 * @return
 */
tDNodeI *tCreateDNodeI(int value) {
    tDNodeI *node = (tDNodeI *) malloc(sizeof(tDNodeI));
    node->value = value;
    return node;
}

/**
 * 创建一个栈
 * @return
 */
tStackI tCreateIStack() {
    tStackI stack;
    stack.size = 0;
    stack.node = tCreateNodeI(INT32_MAX);
    return stack;
}

/**
 * 判断栈是否为空
 * @重载函数
 * @param stack
 * @return
 */
bool tEmpty(tStackI &stack) {
    return !stack.size;
}

/**
 * 向栈中插入元素
 * @重载函数
 * @param stack
 * @param value
 * @return
 */
void tPush(tStackI &stack, int value) {
    tNodeI *node = tCreateNodeI(value);
    node->next = stack.node->next;
    stack.node->next = node;
    stack.size++;
}

/**
 * 从栈中推出元素
 * @重载函数
 * @param stack
 * @return
 */
int tPop(tStackI &stack) {
    if (tEmpty(stack)) {
        tLog("此栈中已无数据");
        return stack.node->value;
    }
    tNodeI *node = stack.node->next;
    stack.node->next = node->next;
    int value = node->value;
    free(node);
    stack.size--;
    return value;
}

/**
 * 查看栈顶元素值
 * @重载函数
 * @param stack
 * @return
 */
int tPeek(tStackI &stack) {
    if (tEmpty(stack)) {
        tLog("此栈中已无数据");
        return -1;
    }
    return stack.node->next->value;
}

tQueueI tCreateQueueI() {
    tQueueI queue;
    queue.size = 0;
    return queue;
}

/**
 * 判断队列是否为空
 * @重载函数
 * @param stack
 * @return
 */
bool tEmpty(tQueueI &queue) {
    return !queue.size;
}

void tPush(tQueueI &queue, int value) {
    tDNodeI *node = tCreateDNodeI(value);
    if (queue.size == 0) {
        queue.head = node;
    } else {
        node->prior = queue.tail;
        queue.tail->next = node;
    }
    queue.tail = node;
    queue.size++;
}

int tPop(tQueueI &queue) {
    if (tEmpty(queue)) {
        tLog("此队列中已无数据");
        return -1;
    }
    tDNodeI *node = queue.head;
    queue.head = node->next;
    int value = node->value;
    free(node);
    queue.size--;
    if (queue.size == 0) {
        queue.tail = queue.head;
    }
    return value;
}

int tPeek(tQueueI &queue) {
    if (tEmpty(queue)) {
        tLog("此队列中已无数据");
        return -1;
    }
    return queue.head->value;
}