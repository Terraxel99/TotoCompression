#pragma once

#include <string>
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "TotoBlock.hpp"
#include "TotoImageConstants.hpp"

#include "../view/TotoConsoleOutput.hpp"

using namespace std;

class TotoImage {

    private:
        string name;
        cv::Mat baseMat;

        ITotoOutput* view;

        vector<TotoBlock> blocks;
        int nbBlocksHorizontal, nbBlocksVertical, blockSize, totalNbBlocks;
        int width, height;

        TotoImage(const string &filePath, const string &name, bool isCompressed = false);

        void createBlocks(int blockSize = DEFAULT_BLOCKSIZE);
        cv::Mat mergeBlocks();

    public:
        static TotoImage fromFile(const string &filePath, bool isCompressed);
        static TotoImage fromFile(const string &filePath, const string &name, bool isCompressed);

        inline TotoBlock* getBlockAt(int x, int y);
        inline TotoBlock* getBlockAt(int position);

        void save(string filePath);
        void show();
        
        void compress();
        void decompress();

        int getNbBlocks();

        ~TotoImage();
};
