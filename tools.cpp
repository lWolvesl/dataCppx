//
// Created by wolves on 2022/7/19.
//
#include "stdio.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

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

void tPrint(char *text) {
    printf("%s", text);
}

void tPrint(int text) {
    printf("%d", text);
}

void tPrintln(char *text) {
    printf("%s\n", text);
}

void tPrintln(int text) {
    printf("%d\n", text);
}

void tPrintln(bool text) {
    printf("%d\n", text);
}

void tLog(char *text) {
    tPrintTime();
    printf("\033[34minfo \033[0m");
    tPrintln(text);
}

void tLog(int text) {
    tPrintTime();
    printf("\033[34minfo \033[0m");
    tPrintln(text);
}

// 输出一段语句表示程序编译完成以下开始执行
void tStart() {
    tLog("Compile complete!");
}

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
