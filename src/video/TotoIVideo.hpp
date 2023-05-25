#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../image/TotoImage.hpp"

using namespace std;

class TotoIVideo {

    private:
        cv::VideoCapture video;
        double fps;
        int frameCount;
        int frameWidth;
        int frameHeight;
        bool isColoured;

        TotoIVideo(const string &filePath);

    public:
        static TotoIVideo fromFile(const string &filePath);

        ~TotoIVideo();

        void compressAndSave(const string &outputPath);
        void decompressAndSave(const string &outputPath);

        void openWriter();
        void closeWriter();
};
