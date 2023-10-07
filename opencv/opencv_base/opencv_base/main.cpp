#include <opencv2\opencv.hpp> 
#include <iostream>

using namespace std;
using namespace cv;

// 1. 图像读取、显示
void test01(Mat &image) {
	imshow("test", image);
}

// 2. 颜色空间转换
void test02(Mat &image) {
	Mat hsv, gray;
	cvtColor(image, hsv, COLOR_BGR2HSV);		// 颜色空间变换
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("1", hsv);
	imshow("2", gray);
}

// 3.图像对象创建与赋值
void test03() {
	// 创建空白图像
	Mat m = Mat::ones(Size(32, 32), CV_8UC3);	// 8位无符号单通道
	// 为每个通道赋值
	m = Scalar(255, 0, 0);
	cout << m.cols << m.rows << m.channels() << endl;
	// cout << m << endl;

	Mat m1;
	m.copyTo(m1);	// 将m复制给m1
	m1 = Scalar(0, 255, 255);

	imshow("m", m);
	imshow("m1", m1);
}

// 像素的读写操作
void test04(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	for (int row = 0; row < h; row++) {
		uchar * current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			// 单通道
			if (dims == 1) {
				int pv = *current_row;
				*current_row++ = 255 - pv;

			}
			// 三通道
			if (dims == 3) {
				Vec3b bgr = image.at<Vec3b>(row, col);
				// 像素点值全部取x = 255-x
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("像素显示", image);

}
// 像素算术操作
void test05(Mat &image) {
	Mat res = Mat::zeros(image.size(), image.type());
	// 创建空白图像
	Mat m = Mat::zeros(image.size(), image.type());
	// 为空白图像的三个通道赋值
	m = Scalar(100, 50, 0);

	//add(image, m, res);
	//subtract(image, m, res);
	//multiply(image, m, res);
	divide(image, m, res);


	//imshow("m", m);
	imshow("res", res);
}

// 滚动条调整图像亮度和对比度
static void on_lightness(int lightness, void *userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, lightness, dst);
	imshow("亮度与对比度调整", dst);
}

static void on_contrast(int lightness, void *userdata) {
	Mat image = *((Mat*)(userdata));
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());

	double contrast = lightness / 100;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("亮度与对比度调整", dst);
}

void test06(Mat &image) {
	namedWindow("亮度与对比调整", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;

	createTrackbar("value_bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("contrast_bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));

	on_lightness(50, &image);
	//on_contrast(50, &image);

}

// 键盘响应
void test07(Mat &image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//key:esc
			break;
		}
		if (c == 49) {//key=1
			std::cout << "key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);	// 颜色变换
		}
		if (c == 50) {//key=2
			std::cout << "key #2" << std::endl;
			cvtColor(image, dst, COLOR_BGR2HSV);
		}
		if (c == 51) {//key=3
			std::cout << "key #3" << std::endl;
			dst = Scalar(40, 20, 30);
			add(image, dst, dst);
		}
		imshow("键盘响应", dst);
	}
}
// 颜色表操作
void test08(Mat &image) {
	Mat dst;
	int colormap[] = {
	COLORMAP_AUTUMN,
	COLORMAP_BONE,
	 COLORMAP_JET,
	 COLORMAP_WINTER,
	 COLORMAP_RAINBOW,
	COLORMAP_OCEAN,
	 COLORMAP_SUMMER,
	COLORMAP_SPRING,
	COLORMAP_COOL,
	COLORMAP_HSV,
	COLORMAP_PINK,
	 COLORMAP_HOT,
	COLORMAP_PARULA,
	  COLORMAP_MAGMA,
	 COLORMAP_INFERNO,
	 COLORMAP_PLASMA,
	COLORMAP_VIRIDIS,
	COLORMAP_CIVIDIS,
	COLORMAP_TWILIGHT,
	COLORMAP_TWILIGHT_SHIFTED,
	};
	int index = 0;
	while (true) {
		int c = waitKey(500);
		if (c == 27) {//key:esc
			break;
		}
		// 要保证取余后数组不能越界
		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		imshow("颜色风格", dst);
	}
}

int main()
{
	Mat img = imread("D:/headImg.jpg");
	if (img.empty())
	{
		cout << "请确认图像文件名是否正确" << endl;
	}

	//test01(img);
	//test02(img);
	//test03();
	//test04(img);
	//test05(img);
	//test06(img);
	//test07(img);
	test08(img);



	waitKey(0);
	return 0;
}