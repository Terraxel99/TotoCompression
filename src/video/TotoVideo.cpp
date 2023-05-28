#include "TotoVideo.hpp"

TotoVideo::TotoVideo(const string &filePath) {
    cv::VideoCapture video(filePath);

    if (!video.isOpened()) {
        throw runtime_error("Could not process video file");
    }

    this->fps = video.get(cv::CAP_PROP_FPS);
    this->frameDelay = 1000 / this->fps;
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

void TotoVideo::showVideo(const string &videoName) {
    cv::namedWindow(videoName);
    cv::setWindowProperty(videoName, cv::WND_PROP_TOPMOST, 1);

    for (int frame = 0; frame < this->frameCount; frame++) {
        cv::imshow(videoName, this->frames.at(frame).mergeBlocks());

        if (cv::waitKey(this->frameDelay) == QUIT_VIDEO_SHOW_KEYCODE) {
            cv::destroyWindow(videoName);
            return;
        }
    }

    cv::waitKey(0);
    cv::destroyWindow(videoName);
}

vector<cv::Mat> TotoVideo::retrieveFrames() {
    vector<cv::Mat> frames;

    for (int frame = 0; frame < this->frameCount; frame++) {
        frames.push_back(this->frames.at(frame).mergeBlocks().clone());
    }

    return frames;
}

double TotoVideo::computePSNR(const vector<cv::Mat> &comparisonFrames) {
    if (comparisonFrames.size() != this->frameCount) {
        throw runtime_error("Both videos must have same frame count.");
    }

    double sum = 0.0;

    for (int frame = 0; frame < this->frameCount; frame++) {
        cv::Mat currentFrame = this->frames.at(frame).mergeBlocks();
        sum += cv::PSNR(comparisonFrames.at(frame), currentFrame);
    }

    return sum / this->frameCount;
}
