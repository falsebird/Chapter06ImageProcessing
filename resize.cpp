#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void dmain() {
	Mat srcImage = imread("1,jpg");
	Mat tempImage, dstImage1,dstImage2;

	tempImage = srcImage;

	imshow("[ԭʼͼ]", srcImage);

	resize(tempImage, dstImage1, Size(tempImage.cols / 2, tempImage.rows / 2), (0, 0), (0, 0));
	resize(tempImage, dstImage2, Size(tempImage.cols * 2, tempImage.rows * 2), (0, 0), (0, 0));

	imshow("[Ч��ͼ]֮һ", dstImage1);
	imshow("[Ч��ͼ]֮��", dstImage2);

	waitKey(0);

}

int main() {
	dmain();
	return 0;
}

