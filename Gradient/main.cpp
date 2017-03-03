#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace cv;

int main(int argc, char** argv)
{
	char* imageName = argv[1];
	
	if (argc != 2 && argc != 3)
	{
		printf("Usage: Gradient.exe <filename> \nOptions: \n-i \t\t Invert the colors of the output image");
		return -1;
	}

	Mat image;
	image = imread(imageName, 1);

	Mat bw_im;
	cvtColor(image, bw_im, CV_BGR2GRAY);

	for (int i = 1; i < bw_im.rows-1; i++) {

		for (int j = 1; j < bw_im.cols-1; j++) {

			bw_im.at<uchar>(i,j) = (10 * bw_im.at<uchar>(i-1, j-1) + 27 * bw_im.at<uchar>(i-1, j) + 10 * bw_im.at<uchar>(i-1, j+1) + 27 * bw_im.at<uchar>(i, j-1) + 74 * bw_im.at<uchar>(i, j) + 27 * bw_im.at<uchar>(i, j+1) + 10 * bw_im.at<uchar>(i+1, j-1) + 27 * bw_im.at<uchar>(i+1, j) + 10 * bw_im.at<uchar>(i+1, j+1)) / 222;

		}

	}

	Mat g_img = Mat(bw_im.rows, bw_im.cols, CV_8UC1, cv::Scalar(0));

	for (int i = 1; i < bw_im.rows-1; i++) {

		for (int j = 1; j < bw_im.cols-1; j++) {

			g_img.at<uchar>(i, j) = sqrt(pow(bw_im.at<uchar>(i+1, j) - bw_im.at<uchar>(i-1, j), 2) + pow(bw_im.at<uchar>(i, j+1) - bw_im.at<uchar>(i, j-1), 2));

		}

	}
	
	if (argc == 3 && (string)argv[2] == "-i") {
		
		for (int i = 0; i < g_img.rows; i++) {

			for (int j = 0; j < g_img.cols; j++) {

				g_img.at<uchar>(i, j) = 255 - g_img.at<uchar>(i, j);

			}

		}

	}

	int x = -1;
	string filename(imageName);

	x = filename.find("\\");
	while (filename.find("\\", x) != filename.npos) {
		filename.erase(0, x+1);
		x = filename.find("\\");
	}

	filename = "gradient" + filename;
	imwrite(filename, g_img);

	return 0;

}