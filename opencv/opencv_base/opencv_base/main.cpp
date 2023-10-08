#include <opencv2\opencv.hpp> 
#include <iostream>

using namespace std;
using namespace cv;

// 1. ͼ���ȡ����ʾ
void test01(Mat &image) {
	imshow("test", image);
}

// 2. ��ɫ�ռ�ת��
void test02(Mat &image) {
	Mat hsv, gray;
	cvtColor(image, hsv, COLOR_BGR2HSV);		// ��ɫ�ռ�任
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("1", hsv);
	imshow("2", gray);
}

// 3.ͼ����󴴽��븳ֵ
void test03() {
	// �����հ�ͼ��
	Mat m = Mat::ones(Size(32, 32), CV_8UC3);	// 8λ�޷��ŵ�ͨ��
	// Ϊÿ��ͨ����ֵ
	m = Scalar(255, 0, 0);
	cout << m.cols << m.rows << m.channels() << endl;
	// cout << m << endl;

	Mat m1;
	m.copyTo(m1);	// ��m���Ƹ�m1
	m1 = Scalar(0, 255, 255);

	imshow("m", m);
	imshow("m1", m1);
}

// ���صĶ�д����
void test04(Mat &image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();

	for (int row = 0; row < h; row++) {
		uchar * current_row = image.ptr<uchar>(row);
		for (int col = 0; col < w; col++) {
			// ��ͨ��
			if (dims == 1) {
				int pv = *current_row;
				*current_row++ = 255 - pv;

			}
			// ��ͨ��
			if (dims == 3) {
				Vec3b bgr = image.at<Vec3b>(row, col);
				// ���ص�ֵȫ��ȡx = 255-x
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
	imshow("������ʾ", image);

}
// ������������
void test05(Mat &image) {
	Mat res = Mat::zeros(image.size(), image.type());
	// �����հ�ͼ��
	Mat m = Mat::zeros(image.size(), image.type());
	// Ϊ�հ�ͼ�������ͨ����ֵ
	m = Scalar(100, 50, 0);

	//add(image, m, res);
	//subtract(image, m, res);
	//multiply(image, m, res);
	divide(image, m, res);


	//imshow("m", m);
	imshow("res", res);
}

// ����������ͼ�����ȺͶԱȶ�
static void on_lightness(int lightness, void *userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, lightness, dst);
	imshow("������Աȶȵ���", dst);
}

static void on_contrast(int lightness, void *userdata) {
	Mat image = *((Mat*)(userdata));
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());

	double contrast = lightness / 100;
	addWeighted(image, contrast, m, 0.0, 0, dst);
	imshow("������Աȶȵ���", dst);
}

void test06(Mat &image) {
	namedWindow("������Աȵ���", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;

	createTrackbar("value_bar:", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("contrast_bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));

	on_lightness(50, &image);
	//on_contrast(50, &image);

}

// ������Ӧ
void test07(Mat &image) {
	Mat dst = Mat::zeros(image.size(), image.type());
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//key:esc
			break;
		}
		if (c == 49) {//key=1
			std::cout << "key #1" << std::endl;
			cvtColor(image, dst, COLOR_BGR2GRAY);	// ��ɫ�任
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
		imshow("������Ӧ", dst);
	}
}
// ��ɫ�����
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
		// Ҫ��֤ȡ������鲻��Խ��
		applyColorMap(image, dst, colormap[index % 19]);
		index++;
		imshow("��ɫ���", dst);
	}
}

int main()
{
	Mat img = imread("D:/headImg.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ����Ƿ���ȷ" << endl;
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