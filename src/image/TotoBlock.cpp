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

void TotoBlock::grayDCT() {
    cv::Mat srcFloat;
    this->data.convertTo(srcFloat, CV_64F);
    cv::dct(srcFloat, this->data);
}

void TotoBlock::colourDCT() {
    cv::Mat srcFloat;
    this->data.convertTo(srcFloat, CV_64F);

    cv::Mat channels[3];
    cv::split(srcFloat, channels);

    for (int i = 0; i < 3; i++) {
        cv::Mat channel;
        channels[i].convertTo(channel, CV_64F);
        cv::dct(channel, channel);
        channel *= 1.0 / sqrt(2.0);
        channels[i] = channel;
    }

    cv::merge(channels, 3, this->data);
}

void TotoBlock::grayIDCT() {
    cv::idct(this->data, this->data);
    this->data.convertTo(this->data, CV_8U);
}

void TotoBlock::colourIDCT() {
    cv::Mat channels[3];
    cv::split(this->data, channels);

    for (int i = 0; i < 3; i++) {
        cv::Mat channel;
        channels[i].convertTo(channel, CV_64F);
        channel *= sqrt(2.0);
        cv::idct(channel, channel);
        channel.convertTo(channel, CV_8U);
        channels[i] = channel;
    }

    cv::merge(channels, 3, this->data);
}

void TotoBlock::DCT() {
    if (this->isColoured()) {
        this->colourDCT();
        return;
    }
    
    this->grayDCT();
}

void TotoBlock::IDCT() {
    if (this->isColoured()) {
        this->colourIDCT();
        return;
    }

    this->grayIDCT();
}

void TotoBlock::tempShow() {
    cv::imshow("Test", this->data);
    cv::waitKey(0);
}
