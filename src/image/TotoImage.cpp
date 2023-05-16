#include "TotoImage.hpp"

TotoImage TotoImage::fromFile(const string &filePath, bool isCompressed) {    
    string name = "TotoImage"; 
    return TotoImage(filePath, name, isCompressed);         
}

TotoImage TotoImage::fromFile(const string &filePath, const string &name, bool isCompressed) {
    return TotoImage(filePath, name, isCompressed);
}

TotoImage::TotoImage(const string &filePath, const string &name, bool isCompressed) {
    this->baseMat = cv::imread(filePath, cv::IMREAD_UNCHANGED);

    double conversionScale = isCompressed ? (1.0 / 255.0) : 1.0;
    this->baseMat.convertTo(this->baseMat, CV_64F, conversionScale);
    
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
    cv::Mat output = cv::Mat(this->baseMat.size().height, this->baseMat.size().width, this->baseMat.type());

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* block = this->getBlockAt(i);
        cv::Mat region = output(cv::Rect(block->getBaseImageXOffset(), block->getBaseImageYOffset(), block->getWidth(), block->getHeight()));

        block->getData().copyTo(region);
    }

    return output;
}

void TotoImage::compress() {
    cout << "Compressing image" << endl;

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* currentBlock = this->getBlockAt(i);

        currentBlock->DCT();
        //currentBlock->quantize();
    }

    this->show();
}

void TotoImage::decompress() {
    cout << "Decompressing image" << endl;

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* currentBlock = this->getBlockAt(i);

        //currentBlock->deQuantize();
        currentBlock->IDCT();
    }

    this->show();
}

void TotoImage::save(string filePath) {
    cv::Mat compressed = this->mergeBlocks();

    cv::imwrite(filePath, compressed);
}

void TotoImage::show() {
    cv::Mat compressed = this->mergeBlocks();

    cv::imshow(this->name, compressed);
    cv::waitKey(0);
}
