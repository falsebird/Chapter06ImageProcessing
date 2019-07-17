#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void boxFil() {
	Mat image = imread("1.jpg");

	namedWindow("�����˲�ԭͼ");
	namedWindow("�����˲�Ч��ͼ");

	imshow("�����˲�ԭͼ", image);

	Mat out;
	boxFilter(image, out, -1, Size(5, 5));

	imshow("�����˲�Ч��ͼ", out);
	waitKey(0);
}

void blurFil() {
	//����ԭͼ
	Mat image = imread("1.jpg");

	//��������
	namedWindow("��ֵ�˲�ԭͼ");
	namedWindow("��ֵ�˲�Ч��ͼ");
	//��ʾԭͼ
	imshow("��ֵ�˲�ԭͼ", image);
	//�����˲�����
	Mat out;
	blur(image, out,  Size(7, 7));
	//��ʾЧ��ͼ
	imshow("��ֵ�˲�Ч��ͼ", out);
	waitKey(0);
}

void GaussianFil() {
	//����ԭͼ
	Mat image = imread("1.jpg");

	//��������
	namedWindow("��˹�˲�ԭͼ");
	namedWindow("��˹�˲�Ч��ͼ");
	//��ʾԭͼ
	imshow("��˹�˲�ԭͼ", image);
	//�����˲�����
	Mat out;
	GaussianBlur(image, out,  Size(3, 3),0,0);
	//��ʾЧ��ͼ
	imshow("��˹�˲�Ч��ͼ", out);
	waitKey(0);
}



int main() {
	GaussianFil();
	boxFil();
	blurFil();
	return 0;
}