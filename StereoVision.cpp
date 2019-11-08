#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include<iostream>

using namespace std;
using namespace cv;
using std::ofstream;

// Calculating disparity map using naive method
Mat getDisparityMapNaive(Mat leftImage, Mat rightImage, int windowSize, int disparityRange) {
	Size imageSize = leftImage.size();

	// Initializing disparity map
	Mat disparityMap = Mat::zeros(imageSize, CV_16UC1);

	// Filling disparity map
	for (int i = windowSize; i < imageSize.height - windowSize; ++i) {
		for (int j = windowSize; j < imageSize.width - windowSize; ++j) {
			int xLeft = j - windowSize;

			// Obtaining window from left image
			Rect leftROI = Rect(xLeft, i - windowSize, 2 * windowSize + 1, 2 * windowSize + 1);
			Mat leftWindow = leftImage(leftROI);

			int minSAD = 9999999;
			int xRight = 0;

			// We are looking for matching window in a range
			int kMin = max(windowSize, j - disparityRange);
			for (int k = kMin; k < j; ++k) {
				// Obtaining window from right image
				Rect rightROI = Rect(k - windowSize, i - windowSize, 2 * windowSize + 1, 2 * windowSize + 1);
				Mat rightWindow = rightImage(rightROI);

				// Calculating sum of absolute differences
				Mat diff;
				absdiff(leftWindow, rightWindow, diff);
				int SAD = sum(diff)[0];

				if (SAD < minSAD) {
					minSAD = SAD;
					xRight = k;
				}
			}

			// Calculating disparity value
			int disparity = abs(xLeft - xRight);
			disparityMap.at<unsigned short>(i, j) = disparity;
		}

		// Displaying process
		cout << i - windowSize + 1 << "/" << imageSize.height - 2 * windowSize << endl;
	}

	Mat disparityMap_CV_8UC1;
	disparityMap.convertTo(disparityMap_CV_8UC1, CV_8UC1);

	return disparityMap_CV_8UC1;
}

// Calculating disparity map using dynamic programming
Mat getDisparityMapDP(Mat leftImage, Mat rightImage, int windowSize, int weight) {
	Size imageSize = leftImage.size();

	// Initializing disparity map
	Mat disparityMap = Mat::zeros(imageSize, CV_16UC1);

	// We are calculating optimal path for each row
	for (int s = windowSize; s < imageSize.height - windowSize; ++s) {
		Mat C = Mat::zeros(Size(imageSize.width - 2 * windowSize, imageSize.width - 2 * windowSize), CV_16UC1);
		Mat M = Mat::zeros(Size(imageSize.width - 2 * windowSize, imageSize.width - 2 * windowSize), CV_8UC1);

		// Initializing C and M 
		C.at<unsigned short>(0, 0) = 0;
		M.at<unsigned char>(0, 0) = 0;
		for (int i = 1; i < C.size().height; ++i) {
			C.at<unsigned short>(i, 0) = i * weight;
			M.at<unsigned char>(i, 0) = 1;
		}
		for (int j = 1; j < C.size().width; ++j) {
			C.at<unsigned short>(0, j) = j * weight;
			M.at<unsigned char>(0, j) = 2;
		}

		// Filling C and M
		for (int r = 1; r < C.size().height; ++r) {
			for (int l = 1; l < C.size().width; ++l) {
				// Obtaining windows
				Rect leftROI = Rect(l, s - windowSize, 2 * windowSize + 1, 2 * windowSize + 1);
				Rect rightROI = Rect(r, s - windowSize, 2 * windowSize + 1, 2 * windowSize + 1);
				Mat leftWindow = leftImage(leftROI);
				Mat rightWindow = rightImage(rightROI);

				// Calculating sum of absolute differences
				Mat diff;
				absdiff(leftWindow, rightWindow, diff);
				int SAD = sum(diff)[0];

				// Calculating cost depending on from where we arrive
				int cMatch = C.at<unsigned short>(r - 1, l - 1) + SAD;
				int cLeftOccl = C.at<unsigned short>(r - 1, l) + weight;
				int cRightOccl = C.at<unsigned short>(r, l - 1) + weight;

				// Minimum cost
				int c = cMatch;
				int m = 0;
				if (cLeftOccl < c) {
					c = cLeftOccl;
					m = 1;
					if (cRightOccl < c) {
						c = cRightOccl;
						m = 2;
					}
				}

				C.at<unsigned short>(r, l) = c;
				M.at<unsigned char>(r, l) = m;
			}
		}

		// Calc disparity map
		int i = M.size().height - 1;
		int j = M.size().width - 1;
		while (j > 0) {
			switch (M.at<unsigned char>(i, j)) {
			case 0:
				disparityMap.at<unsigned short>(s, j) = abs(i - j);
				i--;
				j--;
				break;
			case 1:
				i--;
				break;
			case 2:
				disparityMap.at<unsigned short>(s, j) = 0;
				j--;
				break;
			}
		}

		// Displacing process
		cout << s - windowSize + 1 << "/" << imageSize.height - 2 * windowSize << endl;
	}

	Mat disparityMap_CV_8UC1;
	disparityMap.convertTo(disparityMap_CV_8UC1, CV_8UC1);

	return disparityMap_CV_8UC1;
};

// Calculating X,Y,Z coordinates and printing them into a file
void createPointCloud(Mat disparityMap, float baseline, float focalLength, float dmin, String pointCloudPath) {
	Mat disparityMap_CV_32FC1;
	disparityMap.convertTo(disparityMap_CV_32FC1, CV_32FC1);

	// Initializing coordinate matrices
	Mat X = Mat::zeros(disparityMap.size(), CV_32FC1);
	Mat Y = Mat::zeros(disparityMap.size(), CV_32FC1);
	Mat Z = Mat::zeros(disparityMap.size(), CV_32FC1);

	// Matrices for calculating row and col indices (v and u)
	Mat rowIndices = Mat::zeros(disparityMap.size(), CV_32FC1);
	Mat colIndices = Mat::zeros(disparityMap.size(), CV_32FC1);
	for (int i = 0; i < rowIndices.size().height; ++i) {
		rowIndices.row(i).setTo(Scalar(i));
	}
	for (int i = 0; i < colIndices.size().width; ++i) {
		colIndices.col(i).setTo(Scalar(i));
	}

	// Offset (origin is center of image)
	rowIndices = rowIndices - rowIndices.size().height / 2;
	colIndices = colIndices - colIndices.size().width / 2;

	// Calculating coordinates
	X = -baseline * (colIndices * 2 - (disparityMap_CV_32FC1 + dmin)) / (2 * (disparityMap_CV_32FC1 + dmin));
	Y = (baseline * rowIndices) / (disparityMap_CV_32FC1 + dmin);
	Z = (baseline * focalLength) / (disparityMap_CV_32FC1 + dmin);

	// Printing pointcloud to a file
	ofstream pointCloudFile;

	pointCloudFile.open(pointCloudPath);
	if (!pointCloudFile) {
		cerr << "ERROR: Pointcloud file could not be opened" << endl;
		exit(1);
	}

	for (int i = 0; i < disparityMap.size().height; ++i) {
		for (int j = 0; j < disparityMap.size().width; ++j) {
			pointCloudFile << X.at<float>(i, j) << " " << Y.at<float>(i, j) << " " << Z.at<float>(i, j) << endl;
		}
		cout << i + 1 << "/" << disparityMap.size().height << endl;
	}

	pointCloudFile.close();
}

int main(int argc, char** argv)
{
	if (argc != 12) {
		cout << "11 command line arguments needed: Left image path, Right image path, Disparity map path, Point cloud path, Mode, Window size, Disparity range, Weight, Baseline, Focal length, dmin value" << endl;
		return -1;
	}

	// Reading arguments
	String leftImagePath = argv[1];
	String rightImagePath = argv[2];
	String disparityMapPath = argv[3];
	String pointCloudPath = argv[4];
	String mode = argv[5];
	int windowSize = atoi(argv[6]);
	int disparityRange = atoi(argv[7]);
	int weight = atoi(argv[8]);
	int baseline = atoi(argv[9]);
	int focalLength = atoi(argv[10]);
	int dmin = atoi(argv[11]);

	// Reading left and right images
	Mat leftImage = imread(leftImagePath, IMREAD_GRAYSCALE);
	Mat rightImage = imread(rightImagePath, IMREAD_GRAYSCALE);

	// Calculating disparity map
	Mat disparityMap;
	if (mode == "naive") {
		Mat leftImage_CV_16SC1;
		Mat rightImage_CV_16SC1;
		leftImage.convertTo(leftImage_CV_16SC1, CV_16SC1);
		rightImage.convertTo(rightImage_CV_16SC1, CV_16SC1);
		disparityMap = getDisparityMapNaive(leftImage_CV_16SC1, rightImage_CV_16SC1, windowSize, disparityRange);
	}
	else {
		disparityMap = getDisparityMapDP(leftImage, rightImage, windowSize, weight);
	}

	// Saving disparity map
	imwrite(disparityMapPath, disparityMap);

	// Creating and saving pointcloud
	createPointCloud(disparityMap, baseline, focalLength, dmin, pointCloudPath);

	return 0;
}
