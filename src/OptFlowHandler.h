/*
 * OptFlowHandler.h
 *
 *  Created on: Jan 18, 2016
 *      Author: alex
 */

#ifndef SRC_OPTFLOWHANDLER_H_
#define SRC_OPTFLOWHANDLER_H_
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>


using namespace cv;
using namespace std;

class OptFlowHandler
{
public:
	OptFlowHandler();
	virtual ~OptFlowHandler();
	void findCar(Mat& result);
	void loadVid(string video);
	void threshImage(Mat& threshImg);
	float erodesize = 4;
	float dialatesize = 3;
private:
	UMat img_gray_prev, img_uflow;
	Mat img_thresh, curFrame;

	void threshflow(const Mat& flow, Mat& thresh);
	void blobDetector(const Mat& thresh,const Mat& src, Mat& imgoutput);
	VideoCapture rawVid;
	float scale = .5;


};

#endif /* SRC_OPTFLOWHANDLER_H_ */
