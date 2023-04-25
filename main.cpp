#include <stdio.h>
#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main() {
    
    cv::Mat mat = cv::imread("./data/Colour/monarch.tif");

    cout << "Hello there !" << endl;
    cv::imshow("test", mat);
    cv::waitKey(0);

    return 0;
}
