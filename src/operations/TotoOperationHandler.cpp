#include "TotoOperationHandler.hpp"

TotoOperationHandler::TotoOperationHandler(TotoOperation operation) {
    this->operation = operation;
}

void TotoOperationHandler::printProgramUsage() {
    cout << "Program usage :" << endl;
    cout << "\t--help\t\t\t: To get help about the program" << endl;
    cout << "\t--compress {input_path} [-o {output_path}]\t: To compress the image at {input_path} and save to {output_path} (optional)." << endl;
    cout << "\t--decompress {input_path} [-o {output_path}]\t: To decompress the image at {input_path} and save to {output_path} (optional)." << endl;
}

void TotoOperationHandler::execute() {
    
    if (this->operation.type == TotoOperationType::PrintHelp) {
        this->printProgramUsage();
        return;
    }

    TotoImage image = TotoImage::fromFile(this->operation.inputPath);

    switch (this->operation.type) {

        case TotoOperationType::Compress:
            image.compress();
            break;

        case TotoOperationType::Decompress:
            image.decompress();
            break;

        default:
            cerr << "Unknown operation. Please review arguments." << endl << endl;
            this->printProgramUsage();
            return;
    }

    if (this->operation.outputPath == nullptr) {        
        image.save("Some path");
    } else {
        image.save(this->operation.outputPath);
    }
}
