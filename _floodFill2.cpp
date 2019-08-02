#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//全局变量部分
Mat srcImg, dstImg, grayImg, maskImg;//原始图，目标图，灰度图，掩模图
int g_nFillMode = 1;//满水填充的模式
int g_nlowDifference = 20, g_nUpdifference = 20;//负差最大值，正差最大值
int g_nConnectivity = 4;

