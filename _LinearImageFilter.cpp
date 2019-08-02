#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define G_WINDOS_NAME1 "【<0>原图窗口】"
#define G_WINDOS_NAME2 "【<1>方框滤波】"
#define G_WINDOS_NAME3 "【<2>均值滤波】"
#define G_WINDOS_NAME4 "【<3>高斯滤波】"

//一些全局变量
Mat g_srcImag, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFileterValue = 3;//方框滤波参数
int g_nBlurFileterValue = 3;//均值滤波参数
int g_nGuassianBlurFileterValue = 3;//高斯滤波参数


//三个轨迹条的回调函数
static void on_BoxFilter(int, void*);         //方框滤波
static void on_MeanFilter(int, void*);         //均值滤波
static void on_GaussianFilter(int, void*);         //高斯滤波

bool on_all() {
	//载入原图
	g_srcImag = imread("1.jpg", 1);
	if (g_srcImag.empty()) {
		cout << "读取原图片错误";
		return false;
	}
	//克隆原图到三个Mat对象中
	g_dstImage1 = g_srcImag.clone();
	g_dstImage2 = g_srcImag.clone();
	g_dstImage3 = g_srcImag.clone();

	//显示原图
	namedWindow(G_WINDOS_NAME1);
	imshow(G_WINDOS_NAME1, g_srcImag); 

	//------------------------方框滤波-----------------------
	namedWindow(G_WINDOS_NAME2);
	//创建轨迹条
	createTrackbar("内核值", G_WINDOS_NAME2, &g_nBoxFileterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFileterValue, 0);
	//--------------------------------------------------------
	
	//------------------------均值滤波-----------------------
	namedWindow(G_WINDOS_NAME3);
	//创建轨迹条
	createTrackbar("内核值", G_WINDOS_NAME3, &g_nBlurFileterValue, 40,on_MeanFilter );
	on_MeanFilter(g_nBlurFileterValue, 0);
	//--------------------------------------------------------
	
	//------------------------方框滤波-----------------------
	namedWindow(G_WINDOS_NAME4);
	//创建轨迹条
	createTrackbar("内核值", G_WINDOS_NAME4, &g_nGuassianBlurFileterValue, 40, on_GaussianFilter);
	on_GaussianFilter(g_nGuassianBlurFileterValue, 0);
	//--------------------------------------------------------
	while (char(waitKey(1) != 'q') ){
	
	}
	return  true;
}

//int main() {
//	
//	on_all();
//	return 0;
//}

//三个轨迹条的回调函数

//方框滤波
static void on_BoxFilter(int, void*) {
	//方框滤波操作
	boxFilter(g_srcImag, g_dstImage1, -1, Size(g_nBoxFileterValue + 1, g_nBoxFileterValue + 1));
	//展示窗口
	imshow(G_WINDOS_NAME2, g_dstImage1);
}        
//均值滤波
static void on_MeanFilter(int, void*) {
	//均值滤波操作
	blur(g_srcImag, g_dstImage2, Size(g_nBlurFileterValue + 1, g_nBlurFileterValue + 1));
	//展示窗口
	imshow(G_WINDOS_NAME3, g_dstImage2);
}
//高斯滤波
static void on_GaussianFilter(int, void*) {
	//高斯滤波操作
	GaussianBlur(g_srcImag, g_dstImage3, Size(g_nGuassianBlurFileterValue * 2 + 1, g_nGuassianBlurFileterValue * 2 + 1), 0, 0);
	//展示窗口
	imshow(G_WINDOS_NAME4, g_dstImage3);

}
