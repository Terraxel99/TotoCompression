#include "TotoOperationHandler.hpp"

TotoOperationHandler::TotoOperationHandler(TotoOperation operation) {
    this->operation = operation;

    this->view = new TotoConsoleOutput();
    this->view->welcomeMessage();
}

TotoOperationHandler::~TotoOperationHandler() {
    delete this->view;
}

void TotoOperationHandler::execute() {
    
    if (this->operation.type == TotoOperationType::PrintHelp) {
        this->view->programUsage();
        return;
    }

    bool isBaseImageCompressed = this->operation.type == TotoOperationType::Decompress;
    TotoImage image = TotoImage::fromFile(this->operation.inputPath, isBaseImageCompressed);

    switch (this->operation.type) {

        case TotoOperationType::Compress:
            image.compress();
            break;

        case TotoOperationType::Decompress:
            image.decompress();
            break;

        default:
            cerr << "Unknown operation. Please review arguments." << endl << endl;
            this->view->programUsage();
            return;
    }

    if (this->operation.outputPath == nullptr) {        
        image.save("Some path"); // TODO : Default path
    } else {
        image.save(this->operation.outputPath);
    }
}
