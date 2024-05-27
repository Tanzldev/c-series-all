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
// 像素逻辑操作
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

	//bitwise_not(image, dst);	// 像素点取反
	bitwise_xor(m1, m2, dst);

	imshow("dst", dst);
}

//通道分离和合并
void test10(Mat &image) {
	vector<Mat> mv;
	split(image, mv);

	imshow("b", mv[0]);
	imshow("g", mv[1]);
	imshow("r", mv[2]);

	Mat dst;
	mv[0] = 0;			// 将蓝色b通道全部值为0
	merge(mv, dst);
	imshow("dst", dst);

	int from_to[] = { 0,2,1,1,2,0 };
	mixChannels(&image, 1, &dst, 1, from_to, 3);
	imshow("mix", dst);
}

// 颜色提取与转换
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

// 像素值统计
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

// 随机数与随机颜色
void test13() {
	Mat bg = Mat::zeros(Size(600, 600), CV_8UC3);
	int w = bg.cols;
	int h = bg.rows;
	RNG rng(123456);
	while (true) {
		int c = waitKey(50);
		if (c == 27) {		// 用户按下Esc
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
		
		imshow("随机颜色", bg);
	
	}
}

// 多边形绘制与颜色填充
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
	imshow("多边形绘制", bg);

}
// 像素类型转化与归一化
void test15(Mat &image) {
	Mat dst;
	cout << image.type() << endl;
	image.convertTo(image, CV_32F);
	cout << image.type() << endl;
	normalize(image, dst, 1.0, 0, NORM_MINMAX);

	cout << dst.type() << endl;
	
	imshow("图像归一化", dst);
}

// 图像放缩与插值
void test16(Mat &image) {
	Mat zoomin, zoomout;

	int h = image.cols;
	int w = image.rows;
	resize(image, zoomin, Size(w / 1.5, h / 1.5), 0, 0, INTER_LINEAR);
	resize(image, zoomout, Size(w*1.2, h*1.2), 0, 0, INTER_LINEAR);

	imshow("缩小", zoomin);
	imshow("放大", zoomout);
}

// 图像翻转
void test17(Mat &image) {
	imshow("image", image);
	Mat dst;
	// 0以x轴为镜像，1以y轴为镜像，-1以y=x为轴镜像
	flip(image, dst, 1);		
	imshow("图像翻转", dst);
}
// 图像旋转
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
	imshow("旋转", dst);
}

// 视频文件读取、操作与保存
void test19() {
	VideoCapture capture("F:/ai/deep_sort-master/595.mp4");
	Mat frame;
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int frame_nums = capture.get(CAP_PROP_FRAME_COUNT);
	double frame_fps = capture.get(CAP_PROP_FPS);
	std::cout << "帧宽：" << frame_width << std::endl;
	std::cout << "帧高：" << frame_height << std::endl;
	std::cout << "帧数：" << frame_nums << std::endl;
	std::cout << "帧率：" << frame_fps << std::endl;
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

// 直方图
void test20(Mat &image) {
	// 三通道分离
	std::vector<Mat> bgr_plane;
	split(image, bgr_plane);
	// 定义参数变量
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };
	float hranges[2] = { 0,255 };
	const float *ranges[1] = { hranges };
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	// 计算直方图
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	// 显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);
	Mat histImage = Mat::zeros(Size(hist_w, hist_h), CV_8UC3);
	// 归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	// 绘制直方图曲线
	for (int i = 1; i < bins[0]; i++) {
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*i, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	}
	imshow("直方图", histImage);
	
}

// 二维直方图
void test21(Mat &image) {
	// 2D直方图
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
	imshow("2D灰度直方图", hist_2d);
}

// 直方图均衡化
void test22(Mat &image) {
	Mat gray, dst;
	cvtColor(image, gray, COLOR_RGB2GRAY);
	equalizeHist(gray, dst);
	imshow("直方图均衡化", dst);
}
// 均值滤波
void test23(Mat &image) {
	imshow("img", image);
	Mat dst;
	blur(image, dst, Size(3, 3), Point(-1, -1));
	imshow("滤波图像", dst);
}

// 高斯滤波
void test24(Mat &image) {
	imshow("img", image);
	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 5);
	imshow("高斯模糊", dst);
}

// 双边滤波
void test25(Mat &image) {
	imshow("img", image);
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("双边滤波", dst);
}
int main()
{
	Mat img = imread("D:/headImg.jpg");
	if (img.empty())
	{
		cout << "请确认图像文件名是否正确" << endl;
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