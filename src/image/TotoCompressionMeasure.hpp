#pragma once

#include <opencv2/opencv.hpp>

using namespace std;

class TotoCompressionMeasure {

    public:
        static float PSNR(const string& originalPath, const string& compressedPath);
};