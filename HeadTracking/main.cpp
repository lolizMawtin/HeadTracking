
#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include "faceModel.h"
#include <iostream>

using namespace dlib;
using namespace std;

int main()
{
	try
	{
		cv::VideoCapture cap(0);
		if (!cap.isOpened())
		{
			cerr << "Unable to connect to camera" << endl;
			return 1;
		}

		// Load face detection and pose estimation models.
		frontal_face_detector detector = get_frontal_face_detector();
		std::vector<rectangle> previousFaces; 
		cv::Mat black(480, 640, CV_8UC3, cv::Scalar(0, 0, 0));
		shape_predictor pose_model;
		deserialize("C:\\Users\\GL62VR\\source\\repos\\HeadTracking\\shape_predictor_68_face_landmarks.dat") >> pose_model;
		
		//------------------------------------------------------------------------------------------------------------------

		// Initialize Head 3D model points.
		std::vector<cv::Point3d> model_points;
		model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));               // Nose tip
		model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));          // Chin
		model_points.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));       // Left eye left corner
		model_points.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));        // Right eye right corner
		model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));      // Left Mouth corner
		model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));       // Right mouth corner
		
		// Initialize Assumptions about Camera
		// Camera internals
		//double focal_length = dst.cols; // Approximate focal length.
		//cv::Point2d center = cv::Point2d(im.cols / 2, im.rows / 2);
		//cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << focal_length, 0, center.x, 0, focal_length, center.y, 0, 0, 1);
		//cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type); // Assuming no lens distortion


		// Grab and process frames until the main window is closed by the user.
		while (true)
		{
			// Grab a frame and flip it
			cv::Mat temp;
			if (!cap.read(temp))
			{
				break;
			}
			cv::Mat dst;         
			cout << dst.cols;
			cv::flip(temp, dst, 1);     

			cv_image<bgr_pixel> cimg(dst);
			std::vector<rectangle> faces = detector(cimg);

			if (faces.size() == 0) {
				faces = previousFaces;
			}
			else
				previousFaces = faces; 

			//dst = black;

			for (unsigned long i = 0; i < faces.size(); ++i) {
				full_object_detection face = pose_model(cimg, faces[i]);
				std::vector<cv::Point2d> points = getFace(face);

				//prepare output
				render_face_dot(dst, face);
				
			}

			imshow("poop", dst);
			cv::waitKey(1);

		}
	}

	catch (exception& e)
	{
		cout << e.what() << endl;
	}
}

