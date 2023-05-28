#pragma once

#include "TotoVideo.hpp"

using namespace std;

class TotoBVideo : public TotoVideo {

    private:
        TotoBVideo(const string &filePath);

    public:
        static TotoBVideo fromFile(const string &filePath);

        void compress(const string &videoName = "");
        void decompress(const string &videoName = "");
};
