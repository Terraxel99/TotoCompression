#include "TotoBVideo.hpp"

TotoBVideo TotoBVideo::fromFile(const string &filePath) {
    return TotoBVideo(filePath);
}

TotoBVideo::TotoBVideo(const string &filePath)
    : TotoVideo(filePath) { }

void TotoBVideo::compress(const string &videoName) {
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);
        
        throw runtime_error("T'as oublié de changer l'appel à la ligne d'après");
        currentFrame.compress(); // TODO : change to new decompression method

        if (showVideo) {
            cv::imshow(videoName, currentFrame.mergeBlocks());
            
            if (cv::waitKey(this->frameDelay) == QUIT_VIDEO_SHOW_KEYCODE) {
                showVideo = false;
                cv::destroyWindow(videoName);
            }
        }
    }

    if (showVideo) {
        cv::destroyWindow(videoName);
    }
}

void TotoBVideo::decompress(const string &videoName) {
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);

        throw runtime_error("T'as oublié de changer l'appel à la ligne d'après");
        currentFrame.decompress(); // TODO : change to new decompression method

        if (showVideo) {
            cv::imshow(videoName, currentFrame.mergeBlocks());
            
            if (cv::waitKey(this->frameDelay) == QUIT_VIDEO_SHOW_KEYCODE) {
                showVideo = false;
                cv::destroyWindow(videoName);
            }
        }
    }

    if (showVideo) {
        cv::destroyWindow(videoName);
    }
}