#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{


	panel.setup("Videos");
	panel.add(errode.setup("Erode Size",4,1,6));
	panel.add(dialate.setup("Dilate Size",2,1,6));
	panel.add(curVideoName.setup("","traffic.mp4",250,25));


	panel.add(Videogroup.setup("Videos"));
	setUpButtons();

	flowHandler.loadVid(dir.getFile(0).getAbsolutePath());
	flowHandler.findCar(img_color_temp);

}

//--------------------------------------------------------------
void ofApp::update()
{
	ofBackground(100,100,100);

	flowHandler.findCar(img_color_temp);
	cv::cvtColor(img_color_temp,img_color_temp,COLOR_BGR2RGB);

	flowHandler.dialatesize = dialate;
	flowHandler.erodesize = errode;

	for(int i = 0; i< videos.size(); i++ )
	{
		//cout << videos.at(i).getName() << endl;
		if(videos.at(i))
		{
			flowHandler.loadVid(dir.getFile(i).getAbsolutePath());
			curVideoName = dir.getFile(i).getFileName();
			break;
		}
	}


	setUpButtons();

}

//--------------------------------------------------------------
void ofApp::draw()
{

	ofxCv::drawMat(img_color_temp,0,0);


	panel.draw();

}


void ofApp::setUpButtons()
{
	dir.allowExt("mp4");
	dir.listDir(path);

	videos.clear();
	Videogroup.clear();

	videos.resize(dir.size());
	//cout << dir.size() << std::endl;
	for(int i = 0; i < dir.size(); i++)
	{
		videos.at(i).setup(dir.getFile(i).getFileName());
		Videogroup.add(&videos.at(i));

	}
}
