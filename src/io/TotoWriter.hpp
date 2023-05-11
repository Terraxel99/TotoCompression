#pragma once

#include <opencv2/opencv.hpp>

using namespace std;

class TotoWriter {

    public:
        static void writeImage(cv::Mat img, int blockSize, string filePath);
    
};