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
// �����߼�����
void test09(Mat &image) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);

	rectangle(m1, Rect(100, 100, 80, 80), Scalar(155, 0, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);

	Mat dst;
	//bitwise_and(m1, m2, dst);
	//bitwise_or(m1, m2, dst);

	//bitwise_not(image, dst);	// ���ص�ȡ��
	bitwise_xor(m1, m2, dst);

	imshow("dst", dst);
}

//ͨ������ͺϲ�
void test10(Mat &image) {
	vector<Mat> mv;
	split(image, mv);

	imshow("b", mv[0]);
	imshow("g", mv[1]);
	imshow("r", mv[2]);

	Mat dst;
	mv[0] = 0;			// ����ɫbͨ��ȫ��ֵΪ0
	merge(mv, dst);
	imshow("dst", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("mix", dst);
}

// ��ɫ��ȡ��ת��
void test11(Mat &image) {
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(40, 40, 200);
	bitwise_not(mask, mask);
	image.copyTo(redback, mask);
	imshow("roi", redback);
}

// ����ֵͳ��
void test12(Mat &image) {
	double minv, maxv;
	Point minloc, maxloc;
	vector<Mat> mv;
	split(image, mv);

	for (int i = 0; i < image.channels(); i++) {
		minMaxLoc(mv[i], &minv, &maxv, &minloc, &maxloc, Mat());
		cout << "minx value" << minv << "    max value" << maxv << endl;
	}

	Mat mean, stddev;
	meanStdDev(image, mean, stddev);
	cout << "mean" << mean << "  stddev" << stddev << endl;

	system("pause");
}

// ������������ɫ
void test13() {
	Mat bg = Mat::zeros(Size(600, 600), CV_8UC3);
	int w = bg.cols;
	int h = bg.rows;
	RNG rng(123456);
	while (true) {
		int c = waitKey(50);
		if (c == 27) {		// �û�����Esc
			break;
		}
		int x1 = rng.uniform(0, w);
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, h);
		int y2 = rng.uniform(0, w);

		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);

		bg = Scalar(0, 0, 0);
		line(bg, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 2, 8, 0);
		
		imshow("�����ɫ", bg);
	
	}
}

// ����λ�������ɫ���
void test14() {
	Mat bg = Mat::zeros(Size(512, 512), CV_8UC3);
	Point p1(100, 100);
	Point p2(350, 100);
	Point p3(400, 200);
	Point p4(320, 480);
	Point p5(320, 400);

	vector<Point> pts;
	pts.emplace_back(p1);
	pts.emplace_back(p2);
	pts.emplace_back(p3);
	pts.emplace_back(p4);
	pts.emplace_back(p5);

	vector<vector<Point>> cnts;
	cnts.push_back(pts);
	drawContours(bg, cnts, -1, Scalar(0, 255, 0), 2);
	imshow("����λ���", bg);

}
// ��������ת�����һ��
void test15(Mat &image) {
	Mat dst;
	cout << image.type() << endl;
	image.convertTo(image, CV_32F);
	cout << image.type() << endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);

	cout << dst.type() << endl;
	
	imshow("ͼ���һ��", dst);
}

// ͼ��������ֵ
void test16(Mat &image) {
	Mat zoomin, zoomout;

	int h = image.cols;
	int w = image.rows;
	resize(image, zoomin, Size(w / 1.5, h / 1.5), 0, 0, INTER_LINEAR);
	resize(image, zoomout, Size(w*1.2, h*1.2), 0, 0, INTER_LINEAR);

	imshow("��С", zoomin);
	imshow("�Ŵ�", zoomout);
}

// ͼ��ת
void test17(Mat &image) {
	imshow("image", image);
	Mat dst;
	// 0��x��Ϊ����1��y��Ϊ����-1��y=xΪ�᾵��
	flip(image, dst, 1);		
	imshow("ͼ��ת", dst);
}
// ͼ����ת
void test18(Mat &image) {
	Mat M, dst;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f(w / 2, h / 2), 45, 1.0);
	double cos = abs(M.at<double>(0, 0));
	double sin = abs(M.at<double>(0, 1));

	int nw = w * cos + h * sin;
	int nh = w * sin + h * cos;

	M.at<double>(0, 2) += (nw / 2 - w / 2);
	M.at<double>(1, 2) += (nh / 2 - h / 2);

	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(0, 255, 0));
	imshow("��ת", dst);
}

// ��Ƶ�ļ���ȡ�������뱣��
void test19() {
	VideoCapture capture("F:/ai/deep_sort-master/595.mp4");
	Mat frame;
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int frame_nums = capture.get(CAP_PROP_FRAME_COUNT);
	double frame_fps = capture.get(CAP_PROP_FPS);
	std::cout << "֡��" << frame_width << std::endl;
	std::cout << "֡�ߣ�" << frame_height << std::endl;
	std::cout << "֡����" << frame_nums << std::endl;
	std::cout << "֡�ʣ�" << frame_fps << std::endl;
	VideoWriter writer("D:/opencv/test_flip.mp4", capture.get(CAP_PROP_FOURCC), frame_fps, Size(frame_width, frame_height), true);
	while (true) {
		capture.read(frame);
		flip(frame, frame, 1);
		writer.write(frame);
		if (frame.empty()) {
			break;
		}
		imshow("frame", frame);
		int c = waitKey(10);
		if (c == 27) {
			break;
		}
	}
	capture.release();
	writer.release();
	
}

// ֱ��ͼ
void test20(Mat &image) {
	// ��ͨ������
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// �����������
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float *ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// ����ֱ��ͼ
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	// ��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(Size(hist_w, hist_h), CV_8UC3);
	// ��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// ����ֱ��ͼ����
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("ֱ��ͼ", histImage);
	
}

// ��άֱ��ͼ
void test21(Mat &image) {
	// 2Dֱ��ͼ
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_RGB2HSV);
	int hbins = 30, sbins = 32;
	int hist_bins[] = { hbins,sbins };
	float hrange[] = { 0,180 };
	float srange[] = { 0,360 };
	const float *hs_ranges[] = { hrange,srange };
	int hs_channels[] = { 0,1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	double maxValue = 0.0;
	minMaxLoc(hs_hist, 0, &maxValue, 0, 0);
	int scale = 10;
	Mat hist_2d = Mat::zeros(Size(sbins*scale, sbins*scale), CV_8UC3);
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++) {
			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxValue);
			rectangle(hist_2d, Point(h*scale, s*scale), Point((h + 1)*scale - 1, (s + 1)*scale - 1),
				Scalar::all(intensity));
		}
	}
	applyColorMap(hist_2d, hist_2d, COLORMAP_JET);
	imshow("2D�Ҷ�ֱ��ͼ", hist_2d);
}

// ֱ��ͼ���⻯
void test22(Mat &image) {
	Mat gray, dst;
	cvtColor(image, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯", dst);
}
// ��ֵ�˲�
void test23(Mat &image) {
	imshow("img", image);
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1));
	imshow("�˲�ͼ��", dst);
}

// ��˹�˲�
void test24(Mat &image) {
	imshow("img", image);
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 5);
	imshow("��˹ģ��", dst);
}

// ˫���˲�
void test25(Mat &image) {
	imshow("img", image);
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("˫���˲�", dst);
}
int main()
{
	Mat img = imread("D:/headImg.jpg");
	if (img.empty())
	{
		cout << "��ȷ��ͼ���ļ����Ƿ���ȷ" << endl;
	}

	test01(img);
	//test02(img);
	//test03();
	//test04(img);
	//test05(img);
	//test06(img);
	//test07(img);
	//test08(img);
	//test09(img);
	//test10(img);
	//test11(img);
	//test12(img);
	//test13();
	//test14();
	//test15(img);
	//test16(img);
	//test17(img);
	//test18(img);
	//test19();
	//test20(img);
	//test21(img);
	//test22(img);
	//test23(img);
	//test24(img);
	//test25(img);

	waitKey(0);
	return 0;
}