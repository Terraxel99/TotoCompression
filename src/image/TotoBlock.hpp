#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "TotoImageConstants.hpp"

using namespace std;

class TotoBlock {

    private:
        int width, height;
        int baseImageXOffset, baseImageYOffset;
        cv::Mat data;

        bool isColoured();

    public:
        TotoBlock(cv::Mat baseMat, int xOffset, int yOffset, int blockSize);

        int getWidth();
        int getHeight();
        int getBaseImageXOffset();
        int getBaseImageYOffset();

        const cv::Mat getData();

        void DCT();
        void IDCT();

        void quantize();
        void deQuantize();

        void convertTo(int type, double scale = 1.0, double delta = 0.0);

        void tempShow();
};