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
        int frameCount;
        int frameWidth;
        int frameHeight;
        bool isColoured;

        TotoIVideo(const string &filePath);

    public:
        static TotoIVideo fromFile(const string &filePath);

        void compress();
        void decompress();

        void showVideo(const string &videoName);
};
