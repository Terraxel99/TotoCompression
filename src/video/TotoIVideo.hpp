#pragma once

#include "TotoVideo.hpp"

using namespace std;

class TotoIVideo : public TotoVideo {

    private:
        TotoIVideo(const string &filePath);

    public:
        static TotoIVideo fromFile(const string &filePath);

        void compress(const string &videoName = "");
        void decompress(const string &videoName = "");
};
