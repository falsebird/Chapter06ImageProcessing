#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void boxFil() {
	Mat image = imread("1.jpg");

	namedWindow("方框滤波原图");
	namedWindow("方框滤波效果图");

	imshow("方框滤波原图", image);

	Mat out;
	boxFilter(image, out, -1, Size(5, 5));

	imshow("方框滤波效果图", out);
	waitKey(0);
}

void blurFil() {
	//载入原图
	Mat image = imread("1.jpg");

	//创建窗口
	namedWindow("均值滤波原图");
	namedWindow("均值滤波效果图");
	//显示原图
	imshow("均值滤波原图", image);
	//进行滤波操作
	Mat out;
	blur(image, out,  Size(7, 7));
	//显示效果图
	imshow("均值滤波效果图", out);
	waitKey(0);
}

void GaussianFil() {
	//载入原图
	Mat image = imread("1.jpg");

	//创建窗口
	namedWindow("高斯滤波原图");
	namedWindow("高斯滤波效果图");
	//显示原图
	imshow("高斯滤波原图", image);
	//进行滤波操作
	Mat out;
	GaussianBlur(image, out,  Size(3, 3),0,0);
	//显示效果图
	imshow("高斯滤波效果图", out);
	waitKey(0);
}



int main() {
	GaussianFil();
	boxFil();
	blurFil();
	return 0;
}