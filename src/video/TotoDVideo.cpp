#include "TotoDVideo.hpp"

TotoDVideo TotoDVideo::fromFile(const string &filePath) {
    return TotoDVideo(filePath);
}

TotoDVideo::TotoDVideo(const string &filePath)
    : TotoVideo(filePath) { }

void TotoDVideo::compress(const string &videoName) {
    cv::Mat currentIFrameReference;
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);

        if (frame % GOP_SIZE == 0) {
            currentFrame.compress();
            currentIFrameReference = currentFrame.mergeBlocks(true);
        } else {
            currentFrame.compressWithDifference(currentIFrameReference);
        }

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

void TotoDVideo::decompress(const string &videoName) {
    cv::Mat currentIFrameReference;
    bool showVideo = !videoName.empty();

    if (showVideo) {
        cv::namedWindow(videoName);
        cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);
    }

    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);

        if (frame % GOP_SIZE == 0) {
            currentIFrameReference = currentFrame.mergeBlocks(true);
            currentFrame.decompress();
        } else {
            currentFrame.decompressWithDifference(currentIFrameReference);
        }

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