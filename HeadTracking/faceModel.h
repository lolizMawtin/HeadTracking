
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

void draw_polyline(cv::Mat &img, const dlib::full_object_detection& d, const int start, const int end, bool isClosed = false)
{
	std::vector <cv::Point> points;
	for (int i = start; i <= end; ++i)
	{
		points.push_back(cv::Point(d.part(i).x(), d.part(i).y()));
	}
	cv::polylines(img, points, isClosed, cv::Scalar(255, 0, 0), 2, 16);

}

void render_face(cv::Mat &img, const dlib::full_object_detection& d)
{
	DLIB_CASSERT
	(
		d.num_parts() == 68,
		"\n\t Invalid inputs were given to this function. "
		<< "\n\t d.num_parts():  " << d.num_parts()
	);

	draw_polyline(img, d, 0, 16);           // Jaw line
	draw_polyline(img, d, 17, 21);          // Left eyebrow
	draw_polyline(img, d, 22, 26);          // Right eyebrow
	draw_polyline(img, d, 27, 30);          // Nose bridge
	draw_polyline(img, d, 30, 35, true);    // Lower nose
	draw_polyline(img, d, 36, 41, true);    // Left eye
	draw_polyline(img, d, 42, 47, true);    // Right Eye
	draw_polyline(img, d, 48, 59, true);    // Outer lip
	draw_polyline(img, d, 60, 67, true);    // Inner lip

}

void draw_point(cv::Mat &img, const dlib::full_object_detection& d, const int point, cv::Scalar color = cv::Scalar(255,0,0))
{	
	cv::circle(img, cv::Point(d.part(point).x(), d.part(point).y()), 10, color);
}

void render_face_dot(cv::Mat &img, const dlib::full_object_detection& d)
{
	DLIB_CASSERT
	(
		d.num_parts() == 68,
		"\n\t Invalid inputs were given to this function. "
		<< "\n\t d.num_parts():  " << d.num_parts()
	);

	draw_point(img, d, 30, cv::Scalar(0, 255, 0));		// Nose tip
	draw_point(img, d, 8, cv::Scalar(0, 255, 0));		// Chin
	draw_point(img, d, 36, cv::Scalar(255, 0, 0));		// Left eye left corner
	draw_point(img, d, 45, cv::Scalar(0,0,255));		// Right eye right corner
	draw_point(img, d, 48, cv::Scalar(255, 0, 0));		// Left Mouth corner
	draw_point(img, d, 54, cv::Scalar(0, 0, 255);		// Right mouth corner
}

cv::Point2d getPoint(const dlib::full_object_detection& d, int i) {
	return cv::Point2d(d.part(i).x(), d.part(i).y());
}

std::vector<cv::Point2d> getFace (const dlib::full_object_detection& d)
{
	std::vector<cv::Point2d>image_points;

	image_points.push_back(getPoint(d,30));   // Nose tip
	image_points.push_back(getPoint(d, 8));    // Chin
	image_points.push_back(getPoint(d, 36));     // Left eye left corner
	image_points.push_back(getPoint(d, 45));    // Right eye right corner
	image_points.push_back(getPoint(d, 48));    // Left Mouth corner
	image_points.push_back(getPoint(d, 54));    // Right mouth corner

	return image_points;
}
