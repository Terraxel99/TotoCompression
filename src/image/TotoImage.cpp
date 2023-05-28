#include "TotoImage.hpp"

TotoImage TotoImage::fromFile(const string &filePath, bool isCompressed) {    
    string name = "TotoImage"; 
    return TotoImage(filePath, name, isCompressed);         
}

TotoImage TotoImage::fromFile(const string &filePath, const string &name, bool isCompressed) {
    return TotoImage(filePath, name, isCompressed);
}

TotoImage TotoImage::fromMat(const cv::Mat &mat, const string &name, bool isCompressed) {
    return TotoImage(mat, name, isCompressed);
}

TotoImage::TotoImage(const string &filePath, const string &name, bool isCompressed) {
    this->baseMat = cv::imread(filePath, cv::IMREAD_UNCHANGED);
    this->initialize(name, isCompressed);
}

TotoImage::TotoImage(const cv::Mat &mat, const string &name, bool isCompressed) {
    this->baseMat = mat.clone();
    this->initialize(name, isCompressed);
}

void TotoImage::initialize(const string &name, bool isCompressed) {
    this->name = name;

    baseMat.copyTo(this->original);
    this->baseMat.convertTo(this->baseMat, CV_32F);

    this->createBlocks();

    this->view = new TotoConsoleOutput();
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

cv::Mat TotoImage::getOriginalImage() {
    return this->original;
}

cv::Mat TotoImage::mergeBlocks() {
    cv::Mat output = cv::Mat(this->baseMat.size().height, this->baseMat.size().width, this->baseMat.type());

    for (int i = 0; i < this->totalNbBlocks; i++) {
        TotoBlock* block = this->getBlockAt(i);
        cv::Mat region = output(cv::Rect(block->getBaseImageXOffset(), block->getBaseImageYOffset(), block->getWidth(), block->getHeight()));

        block->getData().copyTo(region);
    }

    output.convertTo(output, CV_8U);

    return output;
}

void TotoImage::compress(bool verbose) {
    if (verbose) {
        this->view->imageCompressing();
    }

    for (int i = 0; i < this->totalNbBlocks; i++) {
        if (verbose) {
            int progressPercentage = ((i + 1) / (float)this->totalNbBlocks) * 100;
            this->view->progressBar(progressPercentage);
        }

        TotoBlock* currentBlock = this->getBlockAt(i);

        currentBlock->DCT();
        currentBlock->quantize();
    }

    if (verbose) {
        this->view->imageCompressionEnded();
        this->show();
    }
}

void TotoImage::decompress(bool verbose) {
    if (verbose) {
        this->view->imageDecompressing();
    }

    for (int i = 0; i < this->totalNbBlocks; i++) {
        if (verbose) {
            int progressPercentage = ((i + 1) / (float)this->totalNbBlocks) * 100;
            this->view->progressBar(progressPercentage);
        }

        TotoBlock* currentBlock = this->getBlockAt(i);

        currentBlock->deQuantize();
        currentBlock->IDCT();
    }

    if (verbose) {
        this->view->imageDecompressionEnded();
        this->show();
    }
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
