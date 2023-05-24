#include "TotoCompressionMeasure.hpp"

double getPSNR(const cv::Mat& I1, const cv::Mat& I2);

float TotoCompressionMeasure::PSNR(const string& originalPath, const string& compressedPath) {
    cv::Mat originalImage, compressedImage;

    try {
        originalImage = cv::imread(originalPath, cv::IMREAD_UNCHANGED);
        compressedImage = cv::imread(compressedPath, cv::IMREAD_UNCHANGED);
        originalImage.convertTo(originalImage, compressedImage.type());
    } catch (exception e) {
        cout << e.what() << endl << endl;
        throw runtime_error("One of the images could not be read. Cannot compute PSNR.");
    }

    return (float)cv::PSNR(originalImage, compressedImage);
}
