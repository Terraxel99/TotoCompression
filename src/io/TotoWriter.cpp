#include "TotoWriter.hpp"

void TotoWriter::writeImage(cv::Mat image, TotoImageMetadata metadata, string filePath) {


    string output_file_name = "./out/output_image.toto";

    cv::FileStorage fs(output_file_name, cv::FileStorage::WRITE);
    fs << "image_data" << image;

    // Release the cv::FileStorage object to flush the data to the file
    fs.release();    
}
