#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define wondosname1 "【原始图】" 
#define wondosname2 "【效果图】" 


void Process() {//膨胀和腐蚀的处理函数

}

void on_TrackbarNumChange(int, void*) {//回调函数

}

void on_ElementSizeChange(int, void*) {//回调函数

}

//展示效果的函数
bool show() {
	Mat g_srcImage = imread("img/1.jpg");
	if (g_srcImage.empty()) {
		cout << "读取图片错误!!~~~";
		return false;
	}
	namedWindow(wondosname1);
}

//函数入口
int main() {

}