#include "TotoIVideo.hpp"

TotoIVideo TotoIVideo::fromFile(const string &filePath) {
    return TotoIVideo(filePath);
}

TotoIVideo::TotoIVideo(const string &filePath) {
    this->video = cv::VideoCapture(filePath);

    if (!this->video.isOpened()) {
        throw runtime_error("Could not process video file");
    }

    this->fps = this->video.get(cv::CAP_PROP_FPS);
    this->frameCount = (int)this->video.get(cv::CAP_PROP_FRAME_COUNT);
    this->frameWidth = (int)this->video.get(cv::CAP_PROP_FRAME_WIDTH);
    this->frameHeight = (int)this->video.get(cv::CAP_PROP_FRAME_HEIGHT);
    this->isColoured = (this->video.get(cv::CAP_PROP_CHANNEL) != 1);
}

TotoIVideo::~TotoIVideo() {
    this->video.release();
}

void TotoIVideo::compressAndSave(const string &outputPath) {
    cv::namedWindow("Video");
    cv::setWindowProperty("Video", cv::WND_PROP_TOPMOST, 1);

    int frameDelay = 1000 / this->fps; // Time (in ms) between frames to meet expected framerate.
    cv::Size size(this->frameWidth, this->frameHeight);

    cv::VideoWriter writer(outputPath + ".avi", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), this->fps, size, this->isColoured);

    for (int frameNb = 0; frameNb < this->frameCount; frameNb++) {
        cv::Mat currentFrame;

        if (!this->video.read(currentFrame)) {
            throw runtime_error("Error occurred while reading frame " + to_string(frameNb));
        }

        string name = "Frame " + to_string(frameNb);
        TotoImage img = TotoImage::fromMat(currentFrame, name, false);

        img.compress();
        cv::Mat result = img.mergeBlocks();
        result.convertTo(result, CV_16U);

        writer.write(result);

        cv::imshow("Video", result);
        cv::waitKey(frameDelay);
    }

    cv::waitKey(0); 
    cv::destroyWindow("Video");
    writer.release();
}

void TotoIVideo::decompressAndSave(const string &outputPath) {
    cv::namedWindow("Video");
    cv::setWindowProperty("Video", cv::WND_PROP_TOPMOST, 1);

    int frameDelay = 1000 / this->fps;
    cv::Size size(this->frameWidth, this->frameHeight);

    cv::VideoWriter writer(outputPath + ".avi", cv::VideoWriter::fourcc('F', 'M', 'P', '4'), this->fps, size, this->isColoured);

    for (int frameNb = 0; frameNb < this->frameCount; frameNb++) {
        cv::Mat currentFrame;

        if (!this->video.read(currentFrame)) {
            throw runtime_error("Error occurred while reading frame " + to_string(frameNb));
        }

        string name = "Frame " + to_string(frameNb);
        TotoImage img = TotoImage::fromMat(currentFrame, name, true);

        img.decompress();
        cv::Mat result = img.mergeBlocks();
        result.convertTo(result, CV_16U);
        
        writer.write(result);


        cv::imshow("Video", result);
        cv::waitKey(frameDelay);
    }

    cv::waitKey(0);
    cv::destroyWindow("Video");
    writer.release();
}
