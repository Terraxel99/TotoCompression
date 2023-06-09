#pragma once

#include <iostream>

#include "ITotoOutput.hpp"

using namespace std;

#define PROGRESSBAR_UNIT 5 // The number of % that one single character represents

class TotoConsoleOutput : public ITotoOutput {

    public:
        void welcomeMessage();

        void imageCompressing();
        void imageDecompressing();

        void displayPSNR(float psnr);

        void progressBar(int percentage);

        void imageCompressionEnded();
        void imageDecompressionEnded();
};
