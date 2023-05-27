#include <stdio.h>
#include <iostream>

#include "image/TotoImage.hpp"

using namespace std;

void benchmarkImage(const string &path);
void benchmarkIVideo(const string &path);
void benchmarkDVideo(const string &path);

int main(int argc, char** argv) {
    
    if (strcmp("--image", argv[1]) == 0) {
        benchmarkImage("./data/grayscale 256/bird.tif");
        benchmarkImage("./data/colour/monarch.tif");
        return 0;
    }

    if (strcmp("--Ivideo", argv[1]) == 0) {
        benchmarkIVideo("./data/grayscale 256/bird.tif");
        return 0;
    }

    if (strcmp("--Dvideo", argv[1]) == 0) {
        benchmarkDVideo("./data/grayscale 256/bird.tif");
        return 0;
    }

    return -1;
}

void benchmarkImage(const string &path) {
    TotoImage img = TotoImage::fromFile(path, false);

    cv::Mat original = img.getOriginalImage();
    cv::imshow("Original", original);

    cout << original.type() << endl;

    img.compress();
    cv::Mat compressed = img.mergeBlocks();
    cv::imshow("Compressed", compressed);

    img.decompress();
    cv::Mat decompressed = img.mergeBlocks();
    decompressed.convertTo(decompressed, CV_8U);
    cv::imshow("Decompressed", decompressed);

    cout << cv::PSNR(original, decompressed, 255.0) << endl;

    cv::waitKey(0);
}

void benchmarkIVideo(const string &path) {

}

void benchmarkDVideo(const string &path) {

}
