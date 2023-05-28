#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>

#include "../image/TotoImage.hpp"

#define QUIT_VIDEO_SHOW_KEYCODE 27 // Escape key is 27

using namespace std;

class TotoIVideo {

    private:
        vector<TotoImage> frames;

        double fps;
        int frameCount, frameWidth, frameHeight, frameDelay;
        bool isColoured;

        TotoIVideo(const string &filePath);

    public:
        static TotoIVideo fromFile(const string &filePath);

        void compress(const string &videoName = "");
        void decompress(const string &videoName = "");

        vector<cv::Mat> retrieveFrames();

        double computePSNR(const vector<cv::Mat> &comparisonFrames);

        void showVideo(const string &videoName);
};
