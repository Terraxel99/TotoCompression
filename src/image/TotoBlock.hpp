#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

class TotoBlock {

    private:
        int width, height;
        int baseImageXOffset, baseImageYOffset;
        cv::Mat data;

        bool isColoured();

        void grayDCT();
        void colourDCT();
        void grayIDCT();
        void colourIDCT();

    public:
        TotoBlock(cv::Mat baseMat, int xOffset, int yOffset, int blockSize);

        int getWidth();
        int getHeight();
        int getBaseImageXOffset();
        int getBaseImageYOffset();

        const cv::Mat getData();

        void DCT();
        void IDCT();

        void tempShow();
};