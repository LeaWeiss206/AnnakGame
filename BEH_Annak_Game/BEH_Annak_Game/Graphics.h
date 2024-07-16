#pragma once

#include <string>
#include <vector>
//#include "WorldMap.h"
#include "Coordination.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

typedef struct ImageInfo {
	shared_ptr<Mat> img;
	int x; 
	int y;
	ImageInfo(shared_ptr<Mat> img, int x, int y) :img(img), x(x), y(y) {};
}ImageInfo;

class Graphics
{
	private:
		vector<ImageInfo> movalbleImages;
	public: 
		string parse_to_img_path(string imgName);
		void printImg(vector<vector<Coordination>> const& worldGrid);
		void addPersonOverlay(shared_ptr<Mat> personImage, int x, int y, double d);
		void addEntityAfterBackground(const string& personImagePath, int x, int y, int size);

		void moveObjectsRandomly();
		/*void addImage(Mat& newResult, Mat const& image, Position pos);

		int addImageAndShow(string img, Position pos);*/
};

