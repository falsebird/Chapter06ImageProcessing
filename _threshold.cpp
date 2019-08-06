#include"head.h"


#define WINDOW_NAME "�����򴰿ڡ�"

//--------------ȫ�ֱ�������-----------------
int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;//ԭʼͼ���Ҷ�ͼ��Ч��ͼ

void test() {
	cout << "helloworld-fromthreshold" << endl;
}
/**
*�켣���ص�����
*/
void on_Threshold(int, void*) {
	//������ֵ����
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	//����Ч��ͼ
	imshow(WINDOW_NAME, g_dstImage);
}
//��ʾ���в����ĺ���
void showThreshold() {
	g_srcImage = imread("img/15.jpg");
	if (g_srcImage.empty()) {
		cout << "ͼƬ��ȡ���󣡣���" << endl;
		return;
	}
	imshow("ԭʼͼ", g_srcImage);
	//����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);
	//�������ڲ���ʾԭʼ����
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//�����켣��
	createTrackbar("ģʽ", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold);
	createTrackbar("����ֵ", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold);
	int key;
	while (true) {
		key = waitKey(20);
		if ((char)key == 27) {
			break;
		}
	}

}