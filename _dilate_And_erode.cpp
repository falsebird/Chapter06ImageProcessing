#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define wondosname1 "��ԭʼͼ��" 
#define wondosname2 "��Ч��ͼ��" 


void Process() {//���ͺ͸�ʴ�Ĵ�����

}

void on_TrackbarNumChange(int, void*) {//�ص�����

}

void on_ElementSizeChange(int, void*) {//�ص�����

}

//չʾЧ���ĺ���
bool show() {
	Mat g_srcImage = imread("img/1.jpg");
	if (g_srcImage.empty()) {
		cout << "��ȡͼƬ����!!~~~";
		return false;
	}
	namedWindow(wondosname1);
}

//�������
int main() {

}