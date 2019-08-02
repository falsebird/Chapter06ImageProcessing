#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//ȫ�ֱ�������
Mat g_srcImg, g_dstImg, g_grayImg, g_maskImg;//ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģͼ
int g_nFillMode = 1;//��ˮ����ģʽ
int g_nlowDifference = 20, g_nUpDifference = 20;//�������ֵ���������ֵ
int g_nConnectivity = 4;//��ʾfloodFill������ʶ���ڰ�λ����ֵͨ
int g_bIsColor = true;//�Ƿ�Ϊ��ɫͼ�ı�ʶ��
bool g_bUseMask = false;//�Ƿ���ʾ��ģ���ڵĲ���ֵ
int g_nNewMaskVal = 255;//�µ����»��Ƶ�����ֵ

static void showHelpText() {

	cout << "��ʾ���������ѡ���ĵ�����ͼ������֮����ĵ㣬���ò�ͬ��ɫ��ע" << endl;
	cout << "��������˵����" << endl;
	cout << "�����ͼ��ʾ�����򣬽�����ˮ���" << endl;
	cout << "���̰�����ESC��- �˳�����" << endl;
	cout << "���̰�����1��-  �л���ɫͼ/�Ҷ�ͼģʽ" << endl;
	cout << "���̰�����2��- ��ʾ/������Ĥ����" << endl;
	cout << "���̰�����3��- �ָ�ԭʼͼ��" << endl;
	cout << "���̰�����4��- ʹ�ÿշ�Χ����ˮ���" << endl;
	cout << "���̰�����5��- ʹ�ý��䡢�̶���Χ����ˮ���" << endl;
	cout << "���̰�����6��- ʹ�ý��䡢������Χ����ˮ���" << endl;
	cout << "���̰�����7��- ������־���ĵͰ�λʹ��4λ������ģʽ" << endl;
	cout << "���̰�����8��- ������־���ĵͰ�λʹ��8λ������ģʽ" << endl;
	/*
	
	*/
}

//           �����ϢOnMouse�ص�����
static void onMouse(int event, int x, int y, int, void *) {
	if (event != EVENT_LBUTTONDOWN) {
		return;
	}

	// ----------------------[����floodfill����֮ǰ��׼��]---------------------------

	Point seed = Point(x, y);
	int lowDifference = g_nFillMode == 0 ? 0 : g_nlowDifference;//�շ�Χ��ˮ����䣬��ֵ����Ϊ0��������Ϊȫ�ֵ�g_nLowDifference
	int upDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//�շ�Χ��ˮ����䣬��ֵ����Ϊ0��������Ϊȫ�ֵ�g_nUpDifference

	//��ʶ����0~7λΪg_nConnectivity ,8~15λΪg_NewMaskVal ���ư�λ��ֵ��16~23λΪcv_FLOODFILEE_FIXED_RANFGE ����0
	int flag = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	
	//�������bgrֵ
	                           
	int b = (unsigned)theRNG() & 255;//�������һ��0-255֮���ֵ
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;

	Rect ccomp;//�����ػ��������С�߽��������
	//���ػ��������ص���ֵ�����ǲ�ɫͼģʽ��ȡScalar(b, g, r);���ǻҶ�ͼģʽȡScalar(r * 0.299 + b * 0.299 + g * 0.299)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299 + b * 0.299 + g * 0.299);
	
	Mat dst = g_bIsColor ? g_dstImg : g_grayImg;//Ŀ��ͼ�ĸ�ֵ

	int area;
	//-----------------------��ʽ����FloodFill����---------------

	if (g_bUseMask) {
		threshold(g_maskImg, g_maskImg, 1, 128, THRESH_BINARY);
		area = floodFill(dst,
			g_maskImg,
			seed,
			newVal,
			&ccomp,
			Scalar(lowDifference, lowDifference, lowDifference),
			Scalar(upDifference, upDifference, upDifference),
			flag);
		imshow("mask", g_maskImg);
	}else{
		area = floodFill(dst,
			seed,
			newVal,
			&ccomp,
			Scalar(lowDifference, lowDifference, lowDifference),
			Scalar(upDifference, upDifference, upDifference),
			flag);
	}
	imshow("Ч��ͼ", dst);
}

//----------------��������--------------

void doMain() {

	g_srcImg = imread("1.jpg", 1);

	if (!g_srcImg.data) { cout << "ͼƬ��ȡ���󣡣�" << endl; return; }
	showHelpText();

	g_srcImg.copyTo(g_dstImg);
	cvtColor(g_srcImg, g_grayImg, COLOR_BGR2GRAY);//ת����ͨ����image0���Ҷ�ͼ
	g_maskImg.create(g_srcImg.rows + 2, g_srcImg.cols + 2, CV_8UC1);//����image0�ĳߴ�����ʼ����ģmask
	
	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);

	//����Trackbar
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nlowDifference, 255, 0);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);

	//���ص�����
	setMouseCallback("Ч��ͼ", onMouse, 0);
	while (true) {
		//����ʾЧ��ͼ
		imshow("Ч��ͼ", g_bIsColor ? g_dstImg : g_grayImg);

		//��ȡ���̰���

		int c = waitKey(0);
		//�ж�esc�Ƿ��£����������Ƴ�
		if ((c & 255) == 27) {
			cout << "�����Ƴ�--------------------" << endl;
			break;
		}
		//���ݰ����Ĳ�ͬ�����и��ֲ���
		switch ((char)c)
		{
			//������̡�1�������£�Ч��ͼ�ڻҶ�ͼ����ɫͼ֮�以��
		case '1':
			if (g_bIsColor) {//��ԭͼΪ��ɫ��ת��Ϊ�Ҷ�ͼ�����ҽ���ģmask����Ԫ������Ϊ0
				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ������ɫģʽ���л�Ϊ���Ҷ�ģʽ��" << endl;
				cvtColor(g_srcImg, g_grayImg, COLOR_BGR2GRAY);
				g_maskImg = Scalar::all(0);//��mask����Ԫ������Ϊ0
				g_bIsColor = false;//����ʶ������Ϊfalse����ʾ��ǰͼ��λ��ɫ���ǻҶ�
			}
			else {//��ԭ��Ϊ�Ҷ�ͼ���㽫ԭ���Ĳ�ͼimage0�ٴο�����image��������ģmask����Ԫ������Ϊ0
				cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ�����Ҷ�ģʽ���л�Ϊ����ɫģʽ��" << endl;
				g_srcImg.copyTo(g_dstImg);
				g_maskImg = Scalar::all(0);
				g_bIsColor = true;//����ʶ������Ϊtrue��ʾ��ǰͼ��ģʽΪ��ɫ
			}
			break;
		case '2':
			if (g_bUseMask) {
				destroyWindow("mask" );
				g_bUseMask = false;
			}
			else {
				namedWindow("mask", 0);
				g_maskImg = Scalar::all(0);
				imshow("mask", g_maskImg);
				g_bUseMask = true;
			}
			break;
			//�������3�����£��ָ�ԭʼͼ��
		case '3':
			cout << "���̡�3�������£��ָ�ԭʼͼ��" << endl;
			g_srcImg.copyTo(g_dstImg);
			cvtColor(g_dstImg, g_grayImg, COLOR_BGR2GRAY);
			g_maskImg = Scalar::all(0);
			break;
			//�������4�����£�ʹ�ÿշ�Χ����ˮ���
		case '4':
			cout << "���̡�4�������£�ʹ�ÿշ�Χ����ˮ���" << endl;
			g_nFillMode = 0;
			break;
			//�������5�����£�ʹ�ý��䣬�̶���Χ����ˮ���
		case '5':
			cout << "���̡�5�������£�ʹ�ý��䣬�̶���Χ����ˮ���" << endl;																																																																																								
			g_nFillMode = 1;
			break;
			//�������6�����£�ʹ�ý��䣬������Χ����ˮ���
		case '6':
			cout << "���̡�6�������£�ʹ�ý��䣬������Χ����ˮ���" << endl;
			g_nFillMode = 0;
			break;
			//�������7�����£�������־���ĵڰ�λʹ�õ�4λ������ģʽ
		case '7':
			cout << "���̡�7�������£�������־���ĵڰ�λʹ�õ�4λ������ģʽ" << endl;
			g_nConnectivity = 4;
			break;
			//�������8�����£�������־���ĵڰ�λʹ�õ�8λ������ģʽ
		case '8':
			cout << "���̡�8�������£�������־���ĵڰ�λʹ�õ�8λ������ģʽ" << endl;
			g_nConnectivity = 8;
			break;
		
		}
	}
}
//�������������������
int main(int argc,char** argv) {
	doMain();

}