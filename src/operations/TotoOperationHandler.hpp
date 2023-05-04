#pragma once

#include "TotoOperation.hpp"
#include "../image/TotoImage.hpp"

class TotoOperationHandler {
    
    private:
        TotoOperation operation;
        void printProgramUsage();
        void askUserForFlow();

    public:
        TotoOperationHandler(TotoOperation operation);

        void execute();
};