#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//ȫ�ֱ�������
Mat srcImg, dstImg, grayImg, maskImg;//ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģͼ
int g_nFillMode = 1;//��ˮ����ģʽ
int g_nlowDifference = 20, g_nUpdifference = 20;//�������ֵ���������ֵ
int g_nConnectivity = 4;

