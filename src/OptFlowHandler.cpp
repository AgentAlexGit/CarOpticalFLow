/*
 * OptFlowHandler.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: alex
 */

#include "OptFlowHandler.h"

OptFlowHandler::OptFlowHandler()
{
	// TODO Auto-generated constructor stub

}

OptFlowHandler::~OptFlowHandler()
{
	// TODO Auto-generated destructor stub
}



void OptFlowHandler::findCar(Mat& result)
{
	Mat tempFrame;
	rawVid >> tempFrame;

	resize(tempFrame,curFrame,Size(tempFrame.cols*scale,tempFrame.rows*scale));

	UMat img_gray;
	cvtColor(curFrame,img_gray,COLOR_RGB2GRAY);

	calcOpticalFlowFarneback(img_gray_prev,img_gray,img_uflow,.5,3,4,2,5,1.1,0);

	Mat imgDetected ,flow;
	img_uflow.copyTo(flow);

	threshflow(flow,img_thresh);
	blobDetector(img_thresh,curFrame,result);

	std::swap(img_gray_prev,img_gray);

}

void OptFlowHandler::loadVid(string video)
{
	rawVid.open(video);
	Mat tempFrame;
	rawVid >> tempFrame;

	resize(tempFrame,curFrame,Size(tempFrame.cols/2,tempFrame.rows/2));
	cvtColor(curFrame,img_gray_prev,COLOR_BGR2GRAY);

}


void OptFlowHandler::threshImage(Mat& threshImg)
{

	threshImg = img_thresh;
}


void OptFlowHandler::threshflow(const Mat& flow, Mat& thresh)
{
	 Mat mag, ang;
	 vector<Mat> splitFlow;
	 split(flow,splitFlow);

	 cartToPolar(splitFlow.at(0),splitFlow.at(1),mag,ang);

	 ang=ang.mul(.5);

	 vector<Mat> magl;

	 split(mag,magl);
	 vector<Mat> angl;
	 split(ang,angl);

	 Mat fillmat(flow.rows,flow.cols,flow.depth(),Scalar::all(25));

	 vector<Mat>  finalMat(3);
	 finalMat.at(1) = magl.at(0);
	 finalMat.at(0) = fillmat;
	 finalMat.at(2) = angl.at(0);

	 Mat bgr_coloredflow(flow.rows,flow.cols,CV_8UC3);
	 merge(finalMat,bgr_coloredflow);

	 Mat gray;
	 cvtColor(bgr_coloredflow,bgr_coloredflow,COLOR_HSV2RGB);
	 cvtColor(bgr_coloredflow,gray,COLOR_RGB2GRAY);

	 Mat output;
	 threshold(gray,output,.03,1,THRESH_BINARY_INV);


	 Mat erodeElement = getStructuringElement(MORPH_RECT,Size(erodesize,erodesize));
	 Mat dialateElement = getStructuringElement(MORPH_RECT,Size(dialatesize,dialatesize));
	 erode(output,output,erodeElement,Point(-1,-1),6);
	 dilate(output,output,dialateElement,Point(-1,-1),7);


	 std::swap(output,thresh);
}

void OptFlowHandler::blobDetector(const Mat& thresh,const Mat& src, Mat& imgoutput)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;


    Mat imgtemp;
    thresh.convertTo(imgtemp,CV_8UC1);
    findContours(imgtemp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE,Point(0,0));


    vector< vector<Point> > finalcontours(contours.size());

    src.copyTo(imgoutput);

    int contourcount =0;
    if(hierarchy.size() > 0)
    {

        for(int index =0; index >= 0; index = hierarchy[index][0])
        {
            Moments moment = moments((Mat)contours[index]);
            double area = moment.m00;

            if(area>400 )
            {

                approxPolyDP(Mat(contours[index]),finalcontours[contourcount],3,true);
                contourcount++;

            }
        }

    }



    finalcontours.resize(contourcount);
    for(int i = 0; i < finalcontours.size(); i++)
        drawContours(imgoutput,finalcontours,i,Scalar(0,255,0));
}


