#include <iostream>
#include <opencv2\opencv.hpp>
#include <math.h>
//20160682 DonginKang

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle){
	cv::Mat output;
	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	cv::Point2f pt(img.cols / 2., img.rows / 2.);

	cv::Rect2f bbox = cv::RotatedRect(pt, img.size(), angle).boundingRect2f();
	//std::cout << "bbok : "<< bbox;
	cv::Mat rotation_matrixs = cv::getRotationMatrix2D(pt, angle, 1.0);
	//std::cout << rotation_matrixs;

	//
	//std::cout << "first, second" << first << second;

	const double PI = 3.1415926;
	angle = angle * PI / 180;

	//cv::Mat_<double> rotation_matrix = (cv::Mat_<double>(2, 2) << cos(angle), -sin(angle), sin(angle), cos(angle));
	//std::cout << "rotation_matrix" << rotation_matrix;
	//Find (x,y)ranges of output
	int width_output = round(abs(img.cols * cos(angle)) + abs(img.rows * sin(angle)));
	int height_output = round(abs(img.cols * sin(angle)) + abs(img.rows * cos(angle)));

	int cx = img.size[1] / 2;
	int cy = img.size[0] / 2;
	int cx_new = (width_output-1) / 2;
	int cy_new = (height_output-1) / 2;

	//printf("input size = %d %d", img.size[0], img.size[1]);
	//std::cout << height_output << width_output;
	//printf("input img size = %d %d", img.cols, img.rows);
	//printf("hiehhtgt : %d , width : %d ", height_output, width_output);
	//Calculate destination coordinates from origin
	
	output = cv::Mat(height_output, width_output, img.type());
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			
			double temp_col = (j)* cos(angle) - (i) * sin(angle);
			// ȸ������ �ö� ��ŭ �����ֱ�
			double temp_row = (j)* sin(angle) + (i) * cos(angle)- cx*2*sin(angle); 
	
			if (temp_col >= 0 && temp_row >= 0 && temp_col < width_output && temp_row < height_output) {
				output.at<cv::Vec3b>(temp_row, temp_col) = img.at<cv::Vec3b>(i,j);
			}

		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////
	cv::imshow("a_output", output); cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	const double PI = 3.1415926;
	//cv::Point2f pt(img.cols / 2., img.rows / 2.);
	//std::cout << "pt is " << pt;

	//cv::Mat rotation_matrixs = cv::getRotationMatrix2D(pt, angle, 1.0);
	angle = angle * PI / 180;

	//cv::Mat_<double> rotation_matrix = (cv::Mat_<double>(2, 2) << cos(angle), -sin(angle), sin(angle), cos(angle));
	//std::cout << rotation_matrix;


	//Calculate 'output' size  from range of output
	int width_output = round(abs(img.cols * cos(angle)) + abs(img.rows * sin(angle)));
	int height_output = round(abs(img.cols * sin(angle)) + abs(img.rows * cos(angle)));
	//rotation_matrixs.at<double>(0, 2) += width_output / 2.0 - img.cols / 2.0;
	//rotation_matrixs.at<double>(1, 2) += height_output / 2.0 - img.rows / 2.0;
	
	int cx = img.size[1]/2;
	int cy = img.size[0]/2;
	int cx_new = (width_output)/ 2;
	int cy_new = (height_output) / 2;
	printf("input size = %d %d", img.size[0], img.size[1]);
	printf("hiehhtgt : %d , width : %d ", height_output, width_output);
	printf("rotated image size = %d %d", cx_new, cy_new);
	std::cout << height_output << width_output;
	printf("input img size = %d %d", img.cols, img.rows);
	
	output = cv::Mat(height_output, width_output, img.type());
	for (int i = 0; i < output.size[0]; i++) {
		for (int j = 0; j < output.size[1]; j++) {
			double temp_col = (j-cx_new)*cos(angle) + (i-cy_new)*sin(angle);
			// ȸ������ �ö� ��ŭ �����ֱ�
			double temp_row = -(j-cx_new)*sin(angle) + (i-cy_new)*cos(angle);
			temp_col+= cx ;
			temp_row += cy;
			if (temp_col >= 0 && temp_row >= 0 && temp_col < img.size[1] && temp_row < img.size[0])
			{	
				output.at<cv::Vec3b>(i, j) = img.at<cv::Vec3b>(temp_row, temp_col);
			}
			else {
				output.at < cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
			}
		}
	}

	cv::imshow("b_output", output); cv::waitKey(0);

	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////
	///// hint : refer annotation /////
	// 
	//Calculate Rotation matrix
	const double PI = 3.1415926;
	//cv::Point2f pt(img.cols / 2., img.rows / 2.);
	//std::cout << "pt is " << pt;

	//cv::Mat rotation_matrixs = cv::getRotationMatrix2D(pt, angle, 1.0);
	angle = angle * PI / 180;

	//cv::Mat_<double> rotation_matrix = (cv::Mat_<double>(2, 2) << cos(angle), -sin(angle), sin(angle), cos(angle));
	//std::cout << rotation_matrix;


	//Calculate 'output' size  from range of output
	int width_output = round(abs(img.cols * cos(angle)) + abs(img.rows * sin(angle)));
	int height_output = round(abs(img.cols * sin(angle)) + abs(img.rows * cos(angle)));
	//rotation_matrixs.at<double>(0, 2) += width_output / 2.0 - img.cols / 2.0;
	//rotation_matrixs.at<double>(1, 2) += height_output / 2.0 - img.rows / 2.0;

	int cx = img.size[1] / 2;
	int cy = img.size[0] / 2;
	int cx_new = (width_output) / 2;
	int cy_new = (height_output) / 2;
	printf("input size = %d %d", img.size[0], img.size[1]);
	printf("hiehhtgt : %d , width : %d ", height_output, width_output);
	printf("rotated image size = %d %d", cx_new, cy_new);
	std::cout << height_output << width_output;
	printf("input img size = %d %d", img.cols, img.rows);

	output = cv::Mat(height_output, width_output, img.type());
	for (int i = 0; i < output.size[0]; i++) {
		for (int j = 0; j < output.size[1]; j++) {
			double temp_col = (j - cx_new) * cos(angle) + (i - cy_new) * sin(angle);

			double temp_row = -(j - cx_new) * sin(angle) + (i - cy_new) * cos(angle);
			temp_col += cx;
			temp_row += cy;


			if (temp_col >= 0 && temp_row >= 0 && temp_col < img.size[1] && temp_row < img.size[0])
			{	
				cv::Point a = cv::Point((int)temp_row, (int)temp_col);
				cv::Point b = cv::Point((int)temp_row, (int)temp_col+1);
				cv::Point c = cv::Point((int)temp_row+1, (int)temp_col);
				cv::Point d = cv::Point((int)temp_row+1, (int)temp_col+1);

				if (a.x == img.size[0] - 1) {
					c = a;
					d = b;
				}
				if (a.y == img.size[1] - 1) {
					b = a;
					d = c;
				}

				output.at<cv::Vec3b>(i, j) = (1 - temp_row + a.x) * (1 - temp_col + a.y) * img.at<cv::Vec3b>(a.x, a.y)
					+ (1 - temp_row + a.x) * (temp_col - a.y)*img.at<cv::Vec3b>(b.x, b.y)
					+ (temp_row - a.x) * (1 - temp_col + a.y) * img.at<cv::Vec3b>(c.x, c.y)
					+ (temp_row - a.x) * (temp_col - a.y)*img.at<cv::Vec3b>(d.x, d.y);
			}
			else {
				output.at < cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
			}
		}
	}

	cv::imshow("b_output", output); cv::waitKey(0);

	return output;
}
int main(void){

	double angle = -15.0f;

	cv::Mat input = cv::imread("lena.jpg");

	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
}