#include "TotoIVideo.hpp"

TotoIVideo TotoIVideo::fromFile(const string &filePath) {
    return TotoIVideo(filePath);
}

TotoIVideo::TotoIVideo(const string &filePath) {
    cv::VideoCapture video(filePath);

    if (!video.isOpened()) {
        throw runtime_error("Could not process video file");
    }

    this->fps = video.get(cv::CAP_PROP_FPS);
    this->frameCount = (int)video.get(cv::CAP_PROP_FRAME_COUNT);
    this->frameWidth = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);
    this->frameHeight = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);
    this->isColoured = (video.get(cv::CAP_PROP_CHANNEL) != 1);

    for (int frame = 0; frame < this->frameCount; frame++) {
        cv::Mat currentFrame;
        
        if (!video.read(currentFrame)) {
            throw runtime_error("Error occurred while reading frame " + to_string(frame));
        }

        const string name = "Frame " + to_string(frame);
        TotoImage img = TotoImage::fromMat(currentFrame, name, false);

        this->frames.push_back(img);
    }

    video.release();
}

void TotoIVideo::showVideo(const string &videoName) {
    int frameDelay = 1000 / this->fps; // Time (in ms) between frames to meet expected framerate.

    cv::namedWindow(videoName);
    cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);

    for (int frame = 0; frame < this->frameCount; frame++) {
        cv::imshow(videoName, this->frames.at(frame).mergeBlocks());

        if (cv::waitKey(frameDelay) == 27) {
            cv::destroyWindow(videoName);
            return;
        }
    }

    cv::waitKey(0);
    cv::destroyWindow(videoName);
}

void TotoIVideo::compress() {
    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);
        currentFrame.compress();
    }
}

void TotoIVideo::decompress() {
    for (int frame = 0; frame < this->frameCount; frame++) {
        TotoImage currentFrame = this->frames.at(frame);
        currentFrame.decompress();
    }
}
