#include <iostream>  
#include "ImageRegistration.h"
using namespace std;

int main()
{
	//【0】改变console字体颜色  
	system("color 1A");

	//【1】载入素材图  
	Mat src1 = imread("test-1.png", 1);
	Mat src2 = imread("test-2.png", 1);
	//////-- Step 1: Detect the keypoints using SURF Detector  
	////int minHessian = 800;
	////SurfFeatureDetector detector(minHessian);
	////std::vector<KeyPoint> keypoints_1, keypoints_2, good_keypoints_1, good_keypoints_2;
	////detector.detect(src1, keypoints_1);
	////detector.detect(src2, keypoints_2);
	////int i, count = 0;

	//////-- Step 2: Calculate descriptors (feature vectors)  
	////SurfDescriptorExtractor extractor;
	////Mat descriptors_1, descriptors_2;
	////extractor.compute(src1, keypoints_1, descriptors_1);
	////extractor.compute(src2, keypoints_2, descriptors_2);

	//////-- Step 3: Matching descriptor vectors with a brute force matcher  
	////FlannBasedMatcher matcher;
	////std::vector< DMatch > matches, good_matches;
	////matcher.match(descriptors_1, descriptors_2, matches);

	//////-- Step 4: Find good matcher  
	////double max_dist = 0; double min_dist = 100;
	////for (int i = 0; i < matches.size(); i++) {
	////	double dist = matches[i].distance;
	////	if (dist < min_dist)
	////		min_dist = dist;
	////	if (dist > max_dist)
	////		max_dist = dist;
	////}

	////for (i = 0; i < descriptors_1.rows; i++) {
	////	if (matches[i].distance < 2 * min_dist) {
	////		count += 1;
	////		good_matches.push_back(matches[i]);
	////		good_keypoints_1.push_back(keypoints_1[matches[i].queryIdx]);
	////		good_keypoints_2.push_back(keypoints_2[matches[i].trainIdx]);
	////	}
	////}

	////std::vector<Point2f> frame1_features_ok, frame2_features_ok;
	////for (int i = 0; i < good_keypoints_1.size(); i++) {
	////	Point2f tmpPoint;
	////	tmpPoint.x = good_keypoints_1[i].pt.x;
	////	tmpPoint.y = good_keypoints_1[i].pt.y;
	////	frame1_features_ok.push_back(tmpPoint);
	////}
	////
	////for (int i = 0; i < good_keypoints_2.size(); i++) {
	////	Point2f tmpPoint;
	////	tmpPoint.x = good_keypoints_2[i].pt.x;
	////	tmpPoint.y = good_keypoints_2[i].pt.y;
	////	frame2_features_ok.push_back(tmpPoint);
	////}
	////
	ImageRegistration llll;
	llll.init(src1, src2);
	//Mat mat = getAffineTransform(frame1_features_ok, frame2_features_ok);
	///*cout << 111 << endl;
	//Mat warp_mat;
	//IplImage img = mat;
	//cvConvert(&img, &warp_mat);*/

	for (int i = 100; i < 150; i++) {
		for (int j = 100; j < 150; j++) {
			Point2f temp = llll.getXY(i, j);
			int temp1 = temp.x;
			int temp2 = temp.y;
			src1.at<cv::Vec3b>(j, i)[0] = 0;
			src1.at<cv::Vec3b>(j, i)[1] = 0;
			src1.at<cv::Vec3b>(j, i)[2] = 0;

			src2.at<cv::Vec3b>(temp2, temp1)[0] = 0;
			src2.at<cv::Vec3b>(temp2, temp1)[1] = 0;
			src2.at<cv::Vec3b>(temp2, temp1)[2] = 0;
		}
	}
	//warpAffine(src1, src2, mat, src2.size());
	cv::namedWindow("Display window1", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display window1", src1);
	cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
	cv::imshow("Display window", src2);
	waitKey(0);
	src1.release();
	src2.release();
	return 0;
}



