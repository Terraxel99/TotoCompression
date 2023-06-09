#include "TotoIVideo.hpp"

TotoIVideo TotoIVideo::fromFile(const string &filePath) {
    return TotoIVideo(filePath);
}

TotoIVideo::TotoIVideo(const string &filePath)
    : TotoVideo(filePath) { }

void TotoIVideo::compress(const string &videoName) {
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);
        currentFrame.compress();

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

void TotoIVideo::decompress(const string &videoName) {
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);
        currentFrame.decompress();

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
