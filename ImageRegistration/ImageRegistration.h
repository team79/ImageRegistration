#pragma once

#include "opencv2/core/core.hpp"  
#include "opencv2/features2d/features2d.hpp"  
#include <opencv2/nonfree/nonfree.hpp>  
#include "opencv.hpp"
#include "highgui.h"
using namespace cv;

class ImageRegistration {
	Mat src1;
	Mat src2;
	void getRegistrationMat();
	Mat transMatrix;
public:
	void init(Mat,Mat);
	Point2f getXY(int,int);
	~ImageRegistration();
};