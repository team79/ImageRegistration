#include "ImageRegistration.h"

ImageRegistration::~ImageRegistration() {
	//cvReleaseMat(&src1);
	//cvReleaseMat(&src2);
	//cvReleaseMat(&transMatrix);
	//src1.release();
	//src2.release();
	//transMatrix.release();
}

void ImageRegistration::getRegistrationMat() {
	//-- Step 1: Detect the keypoints using SURF Detector  
	int minHessian = 800;
	SurfFeatureDetector detector(minHessian);
	std::vector<KeyPoint> keypoints_1, keypoints_2, good_keypoints_1, good_keypoints_2;
	detector.detect(src1, keypoints_1);
	detector.detect(src2, keypoints_2);
	int i, count = 0;

	//-- Step 2: Calculate descriptors (feature vectors)  
	SurfDescriptorExtractor extractor;
	Mat descriptors_1, descriptors_2;
	extractor.compute(src1, keypoints_1, descriptors_1);
	extractor.compute(src2, keypoints_2, descriptors_2);

	//-- Step 3: Matching descriptor vectors with a brute force matcher  
	FlannBasedMatcher matcher;
	std::vector< DMatch > matches, good_matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//-- Step 4: Find good matcher  
	double max_dist = 0; double min_dist = 100;
	for (int i = 0; i < matches.size(); i++) {
		double dist = matches[i].distance;
		if (dist < min_dist)
			min_dist = dist;
		if (dist > max_dist)
			max_dist = dist;
	}

	for (i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance < 2 * min_dist) {
			count += 1;
			good_matches.push_back(matches[i]);
			good_keypoints_1.push_back(keypoints_1[matches[i].queryIdx]);
			good_keypoints_2.push_back(keypoints_2[matches[i].trainIdx]);
		}
	}

	std::vector<Point2f> frame1_features_ok, frame2_features_ok;
	for (int i = 0; i < good_keypoints_1.size(); i++) {
		Point2f tmpPoint;
		tmpPoint.x = good_keypoints_1[i].pt.x;
		tmpPoint.y = good_keypoints_1[i].pt.y;
		frame1_features_ok.push_back(tmpPoint);
	}

	for (int i = 0; i < good_keypoints_2.size(); i++) {
		Point2f tmpPoint;
		tmpPoint.x = good_keypoints_2[i].pt.x;
		tmpPoint.y = good_keypoints_2[i].pt.y;
		frame2_features_ok.push_back(tmpPoint);
	}


	transMatrix = estimateRigidTransform(frame1_features_ok, frame2_features_ok, true);
	//descriptors_1.release();
	//descriptors_2.release();
	//while (!keypoints_1.empty()) {
	//	keypoints_1.pop_back();
	//}
	////detector.release();
}

void ImageRegistration::init(Mat m1, Mat m2) {
	src1 = m1;
	src2 = m2;
	getRegistrationMat();
}

Point2f ImageRegistration::getXY(int X, int Y) {
	Point2f ans;
	Mat t = Mat::ones(3, 1, CV_64F);
	t.at<double>(0, 0) = X;
	t.at<double>(1, 0) = Y;
	t.at<double>(2, 0) = 1;
	Mat x = transMatrix * t;
	ans.x = x.at<double>(0, 0);
	ans.y = x.at<double>(1, 0);
	return ans;
}