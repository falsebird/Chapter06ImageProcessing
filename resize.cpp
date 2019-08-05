#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void dmain() {
	Mat srcImage = imread("1,jpg");
	Mat tempImage, dstImage1,dstImage2;

	tempImage = srcImage;

	imshow("[原始图]", srcImage);

	resize(tempImage, dstImage1, Size(tempImage.cols / 2, tempImage.rows / 2), (0, 0), (0, 0));
	resize(tempImage, dstImage2, Size(tempImage.cols * 2, tempImage.rows * 2), (0, 0), (0, 0));

	imshow("[效果图]之一", dstImage1);
	imshow("[效果图]之二", dstImage2);

	waitKey(0);

}

int main() {
	dmain();
	return 0;
}

