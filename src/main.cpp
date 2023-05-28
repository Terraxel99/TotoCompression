#include <stdio.h>
#include <iostream>

#include "image/TotoImage.hpp"
#include "video/TotoIVideo.hpp"
#include "video/TotoDVideo.hpp"

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
        benchmarkIVideo("./data/video/bus_cif.y4m");
        benchmarkIVideo("./data/video/container_cif.y4m");
        return 0;
    }

    if (strcmp("--Dvideo", argv[1]) == 0) {
        benchmarkDVideo("./data/video/bus_cif.y4m");
        benchmarkDVideo("./data/video/container_cif.y4m");
        return 0;
    }

    return -1;
}

void benchmarkImage(const string &path) {
    TotoImage img = TotoImage::fromFile(path, false);

    cv::Mat original = img.getOriginalImage();
    cv::imshow("Original", original);

    img.compress();
    cv::Mat compressed = img.mergeBlocks();
    cv::imshow("Compressed", compressed);

    img.decompress();
    cv::Mat decompressed = img.mergeBlocks();
    cv::imshow("Decompressed", decompressed);

    cout << cv::PSNR(original, decompressed, 255.0) << endl;

    cv::waitKey(0);
}

void benchmarkIVideo(const string &path) {
    TotoIVideo video = TotoIVideo::fromFile(path);
    vector<cv::Mat> originalFrames = video.retrieveFrames();

    video.showVideo("Original");

    video.compress("Compressed");
    video.decompress("Decompressed");

    cout << video.computePSNR(originalFrames) << endl;
}

void benchmarkDVideo(const string &path) {
    TotoDVideo video = TotoDVideo::fromFile(path);
    vector<cv::Mat> originalFrames = video.retrieveFrames();

    video.showVideo("Original");

    video.compress("Compressed");
    video.decompress("Decompressed");

    cout << video.computePSNR(originalFrames) << endl;
}
