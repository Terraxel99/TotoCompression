#pragma once

#include "../image/TotoImage.hpp"

using namespace std;

class TotoReader {

    public:
        static TotoImage readImage(string filePath);

};