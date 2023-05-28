#pragma once

#include "TotoVideo.hpp"

using namespace std;

class TotoDVideo : public TotoVideo {

    private:
        TotoDVideo(const string &filePath);

    public:
        static TotoDVideo fromFile(const string &filePath);

        void compress(const string &videoName = "");
        void decompress(const string &videoName = "");
};
