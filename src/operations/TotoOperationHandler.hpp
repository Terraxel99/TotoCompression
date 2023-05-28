#pragma once

#include "TotoOperation.hpp"
#include "../image/TotoImage.hpp"
#include "../image/TotoCompressionMeasure.hpp"
#include "../video/TotoIVideo.hpp"

using namespace std;

class TotoOperationHandler {
    
    private:
        ITotoOutput* view;

        TotoOperation operation;

        void executeCompressionOperation();
        void executeImageCompressionOperation();
        void executeIFrameOnlyVideoCompressionOperation();

        void executeDecompressionOperation();
        void executeImageDecompressionOperation();
        void executeIFrameOnlyVideoDecompressionOperation();

        void executePSNROperation();
        void executePrintHelpOperation();

    public:
        TotoOperationHandler(TotoOperation operation);
        ~TotoOperationHandler();

        void execute();
};