#include "TotoBlock.hpp"

TotoBlock::TotoBlock(cv::Mat baseMat, int xOffset, int yOffset, int blockSize) {

    if (xOffset % blockSize != 0 || yOffset % blockSize != 0) {
        throw runtime_error("The offsets are not matching with the block size");
    }

    int baseImageWidth = baseMat.size().width;
    int baseImageHeight = baseMat.size().height;

    this->width = min(blockSize, baseImageWidth - xOffset);
    this->height = min(blockSize, baseImageHeight - yOffset);

    this->baseImageXOffset = xOffset;
    this->baseImageYOffset = yOffset;

    this->data = cv::Mat(baseMat(cv::Rect(xOffset, yOffset, this->width, this->height)));
}

int TotoBlock::getWidth() {
    return this->width;
}

int TotoBlock::getHeight() {
    return this->height;
}

int TotoBlock::getBaseImageXOffset() {
    return this->baseImageXOffset;
}

int TotoBlock::getBaseImageYOffset() {
    return this->baseImageYOffset;
}

const cv::Mat TotoBlock::getData() {
    return this->data;
}

bool TotoBlock::isColoured() {
    return !(this->data.empty()) && this->data.channels() == 3;
}

void TotoBlock::convertTo(int type, double scale, double delta) {
    this->data.convertTo(this->data, type, scale, delta);
}

void TotoBlock::DCT() {
    vector<cv::Mat> channels;
    cv::split(this->data, channels);

    for (int channel = 0; channel < channels.size(); channel++) {
        cv::dct(channels[channel], channels[channel]);
    }

    cv::merge(channels, this->data);
}

void TotoBlock::IDCT() {
    vector<cv::Mat> channels;
    cv::split(this->data, channels);

    for (int channel = 0; channel < channels.size(); channel++) {
        cv::idct(channels[channel], channels[channel]);
    }

    cv::merge(channels, this->data);
}

void TotoBlock::quantize() {
    vector<cv::Mat> channels;
    cv::split(this->data, channels);

    for (int channel = 0; channel < channels.size(); channel++) {
        for (int x = 0; x < channels[channel].size().width; x++) {
            for (int y = 0; y < channels[channel].size().height; y++) {
                channels[channel].at<float>(y, x) = (float)(int)(channels[channel].at<float>(y, x) / quantizationMatrix.at<float>(y, x));
            }
        }
    }

    cv::merge(channels, this->data);
}

void TotoBlock::deQuantize() {
    vector<cv::Mat> channels;
    cv::split(this->data, channels);

    for (int channel = 0; channel < channels.size(); channel++) {        
        for (int x = 0; x < channels[channel].size().width; x++) {
            for (int y = 0; y < channels[channel].size().height; y++) {
                channels[channel].at<float>(y, x) = (float)(int)(channels[channel].at<float>(y, x) * quantizationMatrix.at<float>(y, x));
            }
        }
    }

    cv::merge(channels, this->data);
}

void TotoBlock::tempShow() {
    cv::imshow("Test", this->data);
    cv::waitKey(0);
}
