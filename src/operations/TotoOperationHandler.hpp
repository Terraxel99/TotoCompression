#pragma once

#include "TotoOperation.hpp"
#include "../image/TotoImage.hpp"

class TotoOperationHandler {
    
    private:
        ITotoOutput* view;

        TotoOperation operation;
        void askUserForFlow();

    public:
        TotoOperationHandler(TotoOperation operation);
        ~TotoOperationHandler();

        void execute();
};