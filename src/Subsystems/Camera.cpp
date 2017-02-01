#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/Capture.h"
#include <cmath>
int Camera::EXPOSURE(25);

Camera::Camera() :
	Subsystem("Camera"),
	visionRunning(false)
{
	frc::CameraServer* cs = frc::CameraServer::GetInstance();

	//Camera

	camera = new cs::UsbCamera{"MainCam", 0};
	camera->SetResolution(320, 240);
	camera->SetExposureManual(25);

	//Thread vision
	std::thread mainThread([this, cs](){

		cv::Mat img;

		//MainCamera
		cs::CvSink cvSink("sink_MainCam");
		cvSink.SetSource(*camera);

		//MainServer
		cs::CvSource mainStream("MainStream", cs::VideoMode::kMJPEG, 320, 240, 30);
		cs->AddCamera(mainStream);
		auto mainServer = cs->AddServer("serve_MainStream");
		mainServer.SetSource(mainStream);

		//GripServer
		cs::CvSource gripStream("GripStream", cs::VideoMode::kMJPEG, 320, 240, 30);
		cs->AddCamera(gripStream);
		auto gripServer = cs->AddServer("serve_GripStream");
		gripServer.SetSource(gripStream);

		cv::Mat output(240, 320, CV_8UC3, cv::Scalar(255, 0, 0));

		while(true)
		{
			cvSink.GrabFrame(img);
			mainStream.PutFrame(img);

			if(visionRunning.load())
			{
				frc::DriverStation::ReportError("Vision running loop...");
				Analyse(img, output);
			}

			gripStream.PutFrame(output);
		}

	});
	mainThread.detach();

	//Green light ring
	light = RobotMap::cameraLight;
	light->SetSafetyEnabled(false);

}


void Camera::InitDefaultCommand() {

}


void Camera::StartGrip() {
	light->Set(1);

	camera->SetExposureManual(EXPOSURE);

	frc::DriverStation::ReportError("StartGrip called.");

	visionRunning = true;
}


void Camera::EndGrip(){

	light->Set(0);

	visionRunning = false;

	camera->SetExposureManual(25);
}

void Camera::Analyse(const cv::Mat& img, cv::Mat& output)
{

	pipeline.process(img);
	cv::Mat* image = pipeline.getcvErodeOutput();

	frc::DriverStation::ReportError("# Contours : " + std::to_string(pipeline.getfilterContoursOutput()->size()));

	image->copyTo(output);

	//DEBUG (enlever)
	return;

	//└ complÚter




	std::vector<std::vector<cv::Point> >* contours = pipeline.getfindContoursOutput();

	double centreX, largeur;
	cv::Rect rect;
	if(contours->size() == 1){
		 rect = cv::boundingRect(contours->at(0));




	}
	else if(contours->size() == 2){

		std::vector<cv::Point> tableau;
		tableau = contours->at(0);
		tableau.insert(tableau.end(),contours->at(1) .begin(),contours->at(1).end());
		rect = cv::boundingRect(tableau);

	}
	else
	{
		std::vector<double> scores;
		int min1, min2, dist, distMin(241);
		//trouve min
		for(unsigned int i = 0; i < contours->size() - 1; i++)
		{
			for(unsigned int j = i + 1; j < contours->size(); j++)
			{
				cv::Rect rect1 = cv::boundingRect(i);
				cv::Rect rect2 = cv::boundingRect(j);
				dist = std::abs(rect2.y - rect1.y);

				if( dist < distMin)
				{
					distMin = dist;
					min1 = i;
					min2 = j;
				}
			}
		}


		std::vector<cv::Point> board ;
		board = contours->at(min1);
		board.insert(board.end(), contours->at(min2).begin(), contours->at(min2).end());
		rect = cv::boundingRect(board);




	}

		centreX = rect.x + rect.width / 2.0;
		largeur = rect.width;

		if(callbackFunc)
			callbackFunc(centreX, largeur);

	}





