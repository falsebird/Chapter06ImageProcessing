#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define windosname1 "��ԭʼͼ��" 
#define windosname2 "��Ч��ͼ��" 

Mat g_srcImage, g_dstImage;//ԭʼͼ��Ч��ͼ
int g_nTrackbarNumer = 0;//0��ʾ��ʴerode, 1��ʾ����dilate
int g_nStructElementSize = 3; //�ṹԪ��(�ں˾���)�ĳߴ�

void Process() {//���ͺ͸�ʴ�Ĵ�����
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize, 2 * g_nStructElementSize),
		Point(g_nStructElementSize, g_nStructElementSize));
	if (g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}
	imshow(windosname2, g_dstImage);
}

void on_TrackbarNumChange(int, void*) {//�ص�����
	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����							   
	Process();
}

void on_ElementSizeChange(int, void*) {//�ص�����
	//�ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}

//չʾЧ���ĺ���
bool show() {
	g_srcImage = imread("img/1.jpg");
	if (g_srcImage.empty()) {
		cout << "��ȡͼƬ����!!~~~";
		return false;
	}
	//��ʾԭʼͼ
	namedWindow(windosname1);
	imshow(windosname1, g_srcImage);

	//���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow(windosname2);
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT,
		Size(2 * g_nStructElementSize, 2 * g_nStructElementSize),
		Point(g_nStructElementSize, g_nStructElementSize));
	erode(g_srcImage, g_dstImage, element);
	imshow(windosname2, g_dstImage);
	//�����켣��
	createTrackbar("��ʴ/����", windosname2, &g_nTrackbarNumer, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", windosname2, &g_nStructElementSize, 21, on_TrackbarNumChange);

	while(char(waitKey(1)) != 'q'){}
	return true;

}




//�������
//int main() {
//	show();
//}