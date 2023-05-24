#pragma once

#include "TotoOperation.hpp"
#include "../image/TotoImage.hpp"
#include "../image/TotoCompressionMeasure.hpp"

using namespace std;

class TotoOperationHandler {
    
    private:
        ITotoOutput* view;

        TotoOperation operation;

        void executeCompressionOperation();
        void executeDecompressionOperation();
        void executePSNROperation();
        void executePrintHelpOperation();

    public:
        TotoOperationHandler(TotoOperation operation);
        ~TotoOperationHandler();

        void execute();
};