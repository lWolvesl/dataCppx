//
// Created by wolves on 2022/7/19.
//
#include "stdio.h"
#include "time.h"

//换行
void tools_enter() {
    printf("\n");
}

//打印时间戳
void tools_getTime() {
    char times[128];
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    strftime(times, sizeof(times), "%Y/%m/%d %H:%M:%S ", p);
    printf(times);
}

//输出一段语句表示程序编译完成以下开始执行
void tools_start() {
    tools_getTime();
    printf("Compile complete!\n");
}

void tools_end() {
    tools_getTime();
    printf("Done!\n");
}

void tools_print(char *text) {
    printf("%s", text);
}

void tools_print(int text) {
    printf("%d", text);
}

void tools_print(bool text) {
    printf("%d", text);
}

void tools_log(char *text) {
    tools_getTime();
    tools_print(text);
    printf("\n");
}

void tools_log(int text) {
    tools_getTime();
    tools_print(text);
    printf("\n");
}

void tools_log(bool text) {
    tools_getTime();
    tools_print(text);
    printf("\n");
}


