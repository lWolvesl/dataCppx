# DataCpp

- 算法从思想到实现不能急于求成，需要时间沉淀，需要不断练习
- 关于本人的更多项目请访问主页 <a href="https://github.com/lWolvesl">github</a>

#### 章节对应王道408数据结构册

- 先对基础算法吃透再看题目，如第五章先将先/中/后的递归非递归算法```chapter5/BiTNode.cpp```
  研究完成，再看第五章的题目```chapter5/exercises_5_x.cpp```
- 从第五章（树）开始，结构相对复杂，开始编写详细注释

数据结构 C/C++实现,已更新完第五章

- 项目为cmake项目，需要本地或服务器提供cmake支持
- cmake文件即为根目录下的 ```CMakeLists.txt```文件
- 若需要 ```wolves```提供运行环境支持，请联系我并查看 <a href="https://www.gitlab.wolves.top:46080/demoHub/readme">Introduction</a>

## 克隆项目(以下均可)

- ```git clone https://gitee.com/liwolves/datacppx.git```
- ```git clone https://www.gitlab.wolves.top:46080/wolves/datacppx.git```
- ```git clone https://github.com/lWolvesl/dataCppx.git```

## 更新项目

- ```git pull```


#### 自定义工具集实现为根目录下的```tools.cpp```文件

- 工具集存在C++14后使用的C++关键字，若仅使用C请注释相关爆红代码
- 工具集方法含有详细注释，若出现疑问请提交```issue```
- 工具集默认提供了栈、队列、双端队列以及时间戳打印，字符串处理工具等，详情请见注释