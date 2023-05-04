#include "TotoImage.hpp"

TotoImage TotoImage::fromFile(const string &filePath) {
    time_t _tm =time(NULL);
    struct tm* curtime = localtime(&_tm);
    
    return TotoImage(filePath, asctime(curtime));         
}

TotoImage TotoImage::fromFile(const string &filePath, const string &name) {
    return TotoImage(filePath, name);
}

TotoImage::TotoImage(const string &filePath, const string &name) {
    this->baseMat = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    this->name = name;

    this->createBlocks();
}

inline TotoBlock* TotoImage::getBlockAt(int x, int y) {
    return &(this->blocks.at(y * this->nbBlocksHorizontal + x));
}

inline TotoBlock* TotoImage::getBlockAt(int position) {
    return &(this->blocks.at(position));
}

void TotoImage::createBlocks(int blockSize) {
    this->width = this->baseMat.size().width;
    this->height = this->baseMat.size().height;

    this->blockSize = blockSize;
    this->nbBlocksHorizontal = ceil(this->width/(double)blockSize);
    this->nbBlocksVertical = ceil(this->height/(double)blockSize);
    this->totalNbBlocks = this->nbBlocksHorizontal * this->nbBlocksVertical;

    this->blocks = vector<TotoBlock>();

    for (int blockY = 0; blockY < this->nbBlocksVertical; blockY++) {
        for (int blockX = 0; blockX < this->nbBlocksHorizontal; blockX++) {
            int xOffset = blockSize * blockX;
            int yOffset = blockSize * blockY;

            this->blocks.push_back(TotoBlock(this->baseMat, xOffset, yOffset, blockSize));
        }
    }
}

cv::Mat TotoImage::mergeBlocks() {
    cv::Mat output = cv::Mat(this->baseMat.size().height, this->baseMat.size().width, this->getBlockAt(0)->getData().type());

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* block = this->getBlockAt(i);
        cv::Mat region = output(cv::Rect(block->getBaseImageXOffset(), block->getBaseImageYOffset(), block->getWidth(), block->getHeight()));

        block->getData().copyTo(region);
    }

    return output;
}

void TotoImage::compress() {
    cout << "Compress image" << endl;
    
    for (int i = 0; i < this->totalNbBlocks; i++) {
        this->getBlockAt(i)->DCT();
    }

    this->show();
}

void TotoImage::decompress() {
    cout << "Decompress image" << endl;

    for (int i = 0; i < this->totalNbBlocks; i++) {
        this->getBlockAt(i)->IDCT();
    }

    this->show();
}

void TotoImage::save(string filePath) {
    cv::imwrite(filePath, this->mergeBlocks());
}

void TotoImage::show() {
    cv::Mat compressed = this->mergeBlocks();

    cv::imshow(this->name, compressed);
    cv::waitKey(0);
}
