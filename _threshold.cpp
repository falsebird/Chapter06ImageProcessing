#include"head.h"


#define WINDOW_NAME "【程序窗口】"

//--------------全局变量部分-----------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;//原始图，灰度图，效果图

void test() {
	cout << "helloworld-fromthreshold" << endl;
}
/**
*轨迹条回调函数
*/
void on_Threshold(int, void*) {
	//调用阈值函数
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	//跟新效果图
	imshow(WINDOW_NAME, g_dstImage);
}
//演示进行操作的函数
void showThreshold() {
	g_srcImage = imread("img/15.jpg");
	if (g_srcImage.empty()) {
		cout << "图片读取错误！！！" << endl;
		return;
	}
	imshow("原始图", g_srcImage);
	//存留一份原图的灰度图
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	//创建窗口并显示原始窗口
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//创建轨迹条
	createTrackbar("模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	createTrackbar("参数值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	int key;
	while (true) {
		key = waitKey(20);
		if ((char)key == 27) {
			break;
		}
	}

}