#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "../image/TotoImage.hpp"

#define QUIT_VIDEO_SHOW_KEYCODE 27 // Escape key is 27

using namespace std;

class TotoVideo {

    protected:
        vector<TotoImage> frames;

        double fps;
        int frameCount, frameWidth, frameHeight, frameDelay;
        bool isColoured;

        TotoVideo(const string &filePath);

    public:
        virtual void compress(const string &videoName = "") = 0;
        virtual void decompress(const string &videoName = "") = 0;

        vector<cv::Mat> retrieveFrames();

        double computePSNR(const vector<cv::Mat> &comparisonFrames);

        void showVideo(const string &videoName);
};
