#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define G_WINDOS_NAME1 "��<0>ԭͼ���ڡ�"
#define G_WINDOS_NAME2 "��<1>�����˲���"
#define G_WINDOS_NAME3 "��<2>��ֵ�˲���"
#define G_WINDOS_NAME4 "��<3>��˹�˲���"

//һЩȫ�ֱ���
Mat g_srcImag, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFileterValue = 3;//�����˲�����
int g_nBlurFileterValue = 3;//��ֵ�˲�����
int g_nGuassianBlurFileterValue = 3;//��˹�˲�����


//�����켣���Ļص�����
static void on_BoxFilter(int, void*);         //�����˲�
static void on_MeanFilter(int, void*);         //��ֵ�˲�
static void on_GaussianFilter(int, void*);         //��˹�˲�

bool on_all() {
	//����ԭͼ
	g_srcImag = imread("1.jpg", 1);
	if (g_srcImag.empty()) {
		cout << "��ȡԭͼƬ����";
		return false;
	}
	//��¡ԭͼ������Mat������
	g_dstImage1 = g_srcImag.clone();
	g_dstImage2 = g_srcImag.clone();
	g_dstImage3 = g_srcImag.clone();

	//��ʾԭͼ
	namedWindow(G_WINDOS_NAME1);
	imshow(G_WINDOS_NAME1, g_srcImag); 

	//------------------------�����˲�-----------------------
	namedWindow(G_WINDOS_NAME2);
	//�����켣��
	createTrackbar("�ں�ֵ", G_WINDOS_NAME2, &g_nBoxFileterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFileterValue, 0);
	//--------------------------------------------------------
	
	//------------------------��ֵ�˲�-----------------------
	namedWindow(G_WINDOS_NAME3);
	//�����켣��
	createTrackbar("�ں�ֵ", G_WINDOS_NAME3, &g_nBlurFileterValue, 40,on_MeanFilter );
	on_MeanFilter(g_nBlurFileterValue, 0);
	//--------------------------------------------------------
	
	//------------------------�����˲�-----------------------
	namedWindow(G_WINDOS_NAME4);
	//�����켣��
	createTrackbar("�ں�ֵ", G_WINDOS_NAME4, &g_nGuassianBlurFileterValue, 40, on_GaussianFilter);
	on_GaussianFilter(g_nGuassianBlurFileterValue, 0);
	//--------------------------------------------------------
	while (char(waitKey(1) != 'q') ){
	
	}
	return  true;
}

//int main() {
//	
//	on_all();
//	return 0;
//}

//�����켣���Ļص�����

//�����˲�
static void on_BoxFilter(int, void*) {
	//�����˲�����
	boxFilter(g_srcImag, g_dstImage1, -1, Size(g_nBoxFileterValue + 1, g_nBoxFileterValue + 1));
	//չʾ����
	imshow(G_WINDOS_NAME2, g_dstImage1);
}        
//��ֵ�˲�
static void on_MeanFilter(int, void*) {
	//��ֵ�˲�����
	blur(g_srcImag, g_dstImage2, Size(g_nBlurFileterValue + 1, g_nBlurFileterValue + 1));
	//չʾ����
	imshow(G_WINDOS_NAME3, g_dstImage2);
}
//��˹�˲�
static void on_GaussianFilter(int, void*) {
	//��˹�˲�����
	GaussianBlur(g_srcImag, g_dstImage3, Size(g_nGuassianBlurFileterValue * 2 + 1, g_nGuassianBlurFileterValue * 2 + 1), 0, 0);
	//չʾ����
	imshow(G_WINDOS_NAME4, g_dstImage3);

}
