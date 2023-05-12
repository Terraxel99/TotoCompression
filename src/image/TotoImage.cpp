#include "TotoImage.hpp"

TotoImage TotoImage::fromFile(const string &filePath) {    
    return TotoImage(filePath, "Compressed image");         
}

TotoImage TotoImage::fromFile(const string &filePath, const string &name) {
    return TotoImage(filePath, name);
}

TotoImage::TotoImage(const string &filePath, const string &name) {
    this->baseMat = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    this->name = name;

    cout << "CV_8U : " << CV_8U << endl;
    cout << "CV_8UC1 : " << CV_8UC1 << endl;
    cout << "CV_8UC2 : " << CV_8UC2 << endl;
    cout << "CV_8UC3 : " << CV_8UC3 << endl;
    cout << "CV_64F : " << CV_64F << endl;
    cout << "CV_64FC1 : " << CV_64FC1 << endl;
    cout << "CV_64FC2 : " << CV_64FC2 << endl;
    cout << "CV_64FC3 : " << CV_64FC3 << endl;
    cout << "CV_32F : " << CV_32F << endl;
    cout << "CV_32FC1 : " << CV_32FC1 << endl;
    cout << "CV_32FC2 : " << CV_32FC2 << endl;
    cout << "CV_32FC3 : " << CV_32FC3 << endl << endl;

    cout << "Base mat : " << this->baseMat.type() << endl;

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

        currentBlock->convertTo(CV_64F);

        currentBlock->DCT();
        currentBlock->quantize();

        currentBlock->convertTo(CV_8U);
    }

    this->show();
}

void TotoImage::decompress() {
    cout << "Decompressing image" << endl;

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* currentBlock = this->getBlockAt(i);

        currentBlock->convertTo(CV_64F);

        currentBlock->deQuantize();
        currentBlock->IDCT();

        currentBlock->convertTo(CV_8U);
    }

    this->show();
}

void TotoImage::save(string filePath) {

    /*TotoImageMetadata metadata;
    metadata.blockSize = this->blockSize;
    metadata.height = this->height;
    metadata.width = this->width;*/

    cv::Mat compressed = this->mergeBlocks();
    cout << compressed.type() << endl;

    //compressed.convertTo(compressed, CV_8U);
    //TotoWriter::writeImage(compressed, metadata, "./out/temp.toto");*/

    cv::imwrite(filePath, compressed);
}

void TotoImage::show() {
    cv::Mat compressed = this->mergeBlocks();

    cv::imshow(this->name, compressed);
    cv::waitKey(0);
}
