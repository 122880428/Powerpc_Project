/*
* 文件名称：test.h
* 摘 要：进行一些测试
* 
* 当前版本：1.0
* 作 者：皇陆亚18439432431
* 完成日期：2021 年 7 月 16 日
* 修改内容：这里写一些测试用的函数，目前的任务
* 是测试这个新建的c++工程是否能使用各个资源外设
*
*/

#include <iostream>
#include "YN.h"

using namespace std;

//皇：类的测试
class box
{
public:
	int a;
	int b;
public:
	int square(void);
};

//皇：串口测试
void test_com(void);

//皇：Eigen数学库测试
void test_Eigen(void);

//皇：测试NVram的读写操作
void NVram_test(void);
