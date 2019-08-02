#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;


//全局变量部分
Mat g_srcImg, g_dstImg, g_grayImg, g_maskImg;//原始图，目标图，灰度图，掩模图
int g_nFillMode = 1;//满水填充的模式
int g_nlowDifference = 20, g_nUpDifference = 20;//负差最大值，正差最大值
int g_nConnectivity = 4;//表示floodFill函数标识符第八位的联通值
int g_bIsColor = true;//是否为彩色图的标识符
bool g_bUseMask = false;//是否显示掩模窗口的布尔值
int g_nNewMaskVal = 255;//新的重新绘制的像素值

static void showHelpText() {

	cout << "本示例根据鼠标选区的点搜索图像中与之相近的点，并用不同颜色标注" << endl;
	cout << "按键操作说明：" << endl;
	cout << "鼠标点击图中示例区域，进行漫水填充" << endl;
	cout << "键盘按键【ESC】- 退出程序" << endl;
	cout << "键盘按键【1】-  切换彩色图/灰度图模式" << endl;
	cout << "键盘按键【2】- 显示/隐藏掩膜窗口" << endl;
	cout << "键盘按键【3】- 恢复原始图像" << endl;
	cout << "键盘按键【4】- 使用空范围的漫水填充" << endl;
	cout << "键盘按键【5】- 使用渐变、固定范围的漫水填充" << endl;
	cout << "键盘按键【6】- 使用渐变、浮动范围的漫水填充" << endl;
	cout << "键盘按键【7】- 操作标志符的低八位使用4位的连接模式" << endl;
	cout << "键盘按键【8】- 操作标志符的低八位使用8位的连接模式" << endl;
	/*
	
	*/
}

//           鼠标消息OnMouse回调函数
static void onMouse(int event, int x, int y, int, void *) {
	if (event != EVENT_LBUTTONDOWN) {
		return;
	}

	// ----------------------[调用floodfill函数之前的准备]---------------------------

	Point seed = Point(x, y);
	int lowDifference = g_nFillMode == 0 ? 0 : g_nlowDifference;//空范围的水漫填充，此值设置为0，否则设为全局的g_nLowDifference
	int upDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//空范围的水漫填充，此值设置为0，否则设为全局的g_nUpDifference

	//标识符的0~7位为g_nConnectivity ,8~15位为g_NewMaskVal 左移八位的值，16~23位为cv_FLOODFILEE_FIXED_RANFGE 或者0
	int flag = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	
	//随机生成bgr值
	                           
	int b = (unsigned)theRNG() & 255;//随机返回一个0-255之间的值
	int g = (unsigned)theRNG() & 255;
	int r = (unsigned)theRNG() & 255;

	Rect ccomp;//定义重绘区域的最小边界矩形区域
	//在重回区域像素的新值，若是彩色图模式，取Scalar(b, g, r);若是灰度图模式取Scalar(r * 0.299 + b * 0.299 + g * 0.299)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r * 0.299 + b * 0.299 + g * 0.299);
	
	Mat dst = g_bIsColor ? g_dstImg : g_grayImg;//目标图的赋值

	int area;
	//-----------------------正式调用FloodFill函数---------------

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
	imshow("效果图", dst);
}

//----------------主函数体--------------

void doMain() {

	g_srcImg = imread("1.jpg", 1);

	if (!g_srcImg.data) { cout << "图片读取错误！！" << endl; return; }
	showHelpText();

	g_srcImg.copyTo(g_dstImg);
	cvtColor(g_srcImg, g_grayImg, COLOR_BGR2GRAY);//转化三通道的image0到灰度图
	g_maskImg.create(g_srcImg.rows + 2, g_srcImg.cols + 2, CV_8UC1);//利用image0的尺寸来初始化掩模mask
	
	namedWindow("效果图", WINDOW_AUTOSIZE);

	//创建Trackbar
	createTrackbar("负差最大值", "效果图", &g_nlowDifference, 255, 0);
	createTrackbar("正差最大值", "效果图", &g_nUpDifference, 255, 0);

	//鼠标回调函数
	setMouseCallback("效果图", onMouse, 0);
	while (true) {
		//先显示效果图
		imshow("效果图", g_bIsColor ? g_dstImg : g_grayImg);

		//获取键盘按键

		int c = waitKey(0);
		//判断esc是否按下，若按下则推出
		if ((c & 255) == 27) {
			cout << "程序推出--------------------" << endl;
			break;
		}
		//根据按键的不同，进行各种操作
		switch ((char)c)
		{
			//如果键盘‘1’被按下，效果图在灰度图，彩色图之间互换
		case '1':
			if (g_bIsColor) {//若原图为彩色，转化为灰度图，并且将掩模mask所有元素设置为0
				cout << "键盘‘1’被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】" << endl;
				cvtColor(g_srcImg, g_grayImg, COLOR_BGR2GRAY);
				g_maskImg = Scalar::all(0);//将mask所有元素设置为0
				g_bIsColor = false;//将标识符设置为false，表示当前图像部位彩色而是灰度
			}
			else {//若原来为灰度图，便将原来的彩图image0再次拷贝给image，并将掩模mask所有元素设置为0
				cout << "键盘‘1’被按下，切换彩色/灰度模式，当前操作为将【灰度模式】切换为【彩色模式】" << endl;
				g_srcImg.copyTo(g_dstImg);
				g_maskImg = Scalar::all(0);
				g_bIsColor = true;//将标识符设置为true表示当前图像模式为彩色
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
			//如果键盘3被按下，恢复原始图像
		case '3':
			cout << "键盘‘3’被按下，恢复原始图像" << endl;
			g_srcImg.copyTo(g_dstImg);
			cvtColor(g_dstImg, g_grayImg, COLOR_BGR2GRAY);
			g_maskImg = Scalar::all(0);
			break;
			//如果键盘4被按下，使用空范围的漫水填充
		case '4':
			cout << "键盘‘4’被按下，使用空范围的漫水填充" << endl;
			g_nFillMode = 0;
			break;
			//如果键盘5被按下，使用渐变，固定范围的漫水填充
		case '5':
			cout << "键盘‘5’被按下，使用渐变，固定范围的漫水填充" << endl;																																																																																								
			g_nFillMode = 1;
			break;
			//如果键盘6被按下，使用渐变，浮动范围的漫水填充
		case '6':
			cout << "键盘‘6’被按下，使用渐变，浮动范围的漫水填充" << endl;
			g_nFillMode = 0;
			break;
			//如果键盘7被按下，操作标志符的第八位使用的4位的连接模式
		case '7':
			cout << "键盘‘7’被按下，操作标志符的第八位使用的4位的连接模式" << endl;
			g_nConnectivity = 4;
			break;
			//如果键盘8被按下，操作标志符的第八位使用的8位的连接模式
		case '8':
			cout << "键盘‘8’被按下，操作标志符的第八位使用的8位的连接模式" << endl;
			g_nConnectivity = 8;
			break;
		
		}
	}
}
//主函数，，，程序入口
int main(int argc,char** argv) {
	doMain();

}