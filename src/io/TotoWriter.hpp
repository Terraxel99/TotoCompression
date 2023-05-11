#pragma once

#include <opencv2/opencv.hpp>

#include "TotoImageMetadata.hpp"
#include "../image/TotoBlock.hpp"

using namespace std;

class TotoWriter {

    public:
        static void writeImage(cv::Mat image, TotoImageMetadata metadata, string filePath);
    
};