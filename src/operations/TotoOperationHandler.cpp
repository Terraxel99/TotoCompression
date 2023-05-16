#include "TotoOperationHandler.hpp"

TotoOperationHandler::TotoOperationHandler(TotoOperation operation) {
    this->operation = operation;
}

void TotoOperationHandler::execute() {
    
    if (this->operation.type == TotoOperationType::PrintHelp) {
        //this->printProgramUsage(); // TODO : refer to a view
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
            //this->printProgramUsage(); // TODO : refer to a view
            return;
    }

    if (this->operation.outputPath == nullptr) {        
        image.save("Some path");
    } else {
        image.save(this->operation.outputPath);
    }
}
