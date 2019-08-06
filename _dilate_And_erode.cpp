#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define windosname1 "【原始图】" 
#define windosname2 "【效果图】" 

Mat g_srcImg_dli, g_dstImg_dli;//原始图和效果图
int g_nTrackbarNumer = 0;//0表示腐蚀erode, 1表示膨胀dilate
int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸

void Process() {//膨胀和腐蚀的处理函数
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize, 2 * g_nStructElementSize),
		Point(g_nStructElementSize, g_nStructElementSize));
	if (g_nTrackbarNumer == 0) {
		erode(g_srcImg_dli, g_dstImg_dli, element);
	}
	else {
		dilate(g_srcImg_dli, g_dstImg_dli, element);
	}
	imshow(windosname2, g_dstImg_dli);
}

void on_TrackbarNumChange(int, void*) {//回调函数
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来							   
	Process();
}

void on_ElementSizeChange(int, void*) {//回调函数
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

//展示效果的函数
bool show() {
	g_srcImg_dli = imread("img/1.jpg");
	if (g_srcImg_dli.empty()) {
		cout << "读取图片错误!!~~~";
		return false;
	}
	//显示原始图
	namedWindow(windosname1);
	imshow(windosname1, g_srcImg_dli);

	//进行初次腐蚀操作并显示效果图
	namedWindow(windosname2);
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize, 2 * g_nStructElementSize),
		Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImg_dli, g_dstImg_dli, element);
	imshow(windosname2, g_dstImg_dli);
	//创建轨迹条
	createTrackbar("腐蚀/膨胀", windosname2, &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", windosname2, &g_nStructElementSize, 21, on_TrackbarNumChange);

	while(char(waitKey(1)) != 'q'){}
	return true;

}




//函数入口
//int main() {
//	show();
//}