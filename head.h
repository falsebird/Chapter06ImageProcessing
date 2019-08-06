#pragma once


#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//---------------------------------------------------------------
//-                      方法定义部分                           -
//---------------------------------------------------------------
//测试调用其他cpp文件函数的函数
void test();
//轨迹条回调的函数
void on_Threshold(int, void*);
//演示进行操作的函数
void showThreshold();


