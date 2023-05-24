#include "TotoOperationHandler.hpp"

TotoOperationHandler::TotoOperationHandler(TotoOperation operation) {
    this->operation = operation;

    this->view = new TotoConsoleOutput();
    this->view->welcomeMessage();
}

TotoOperationHandler::~TotoOperationHandler() {
    delete this->view;
}

void TotoOperationHandler::executeCompressionOperation() {
    bool isBaseImageCompressed = this->operation.type == TotoOperationType::Decompress;
    TotoImage image = TotoImage::fromFile(this->operation.inputPath, isBaseImageCompressed);

    image.compress();

    image.save(this->operation.outputPath);
}

void TotoOperationHandler::executeDecompressionOperation() {
    bool isBaseImageCompressed = this->operation.type == TotoOperationType::Decompress;
    TotoImage image = TotoImage::fromFile(this->operation.inputPath, isBaseImageCompressed);

    image.decompress();

    image.save(this->operation.outputPath);
}

void TotoOperationHandler::executePSNROperation() {
    float psnr = TotoCompressionMeasure::PSNR(this->operation.inputPath, this->operation.outputPath);
    this->view->displayPSNR(psnr);
}

void TotoOperationHandler::executePrintHelpOperation() {
    this->view->programUsage();
}

void TotoOperationHandler::execute() {
    switch (this->operation.type) {
        case TotoOperationType::PrintHelp:
            this->executePrintHelpOperation();
            break;

        case TotoOperationType::Compress:
            this->executeCompressionOperation();
            break;

        case TotoOperationType::Decompress:
            this->executeDecompressionOperation();
            break;

        case TotoOperationType::PSNR:
            this->executePSNROperation();
            break;

        case TotoOperationType::Unknown:
        default:
            this->executePrintHelpOperation();
            throw runtime_error("Unknown operation. Please review program arguments.");
    }
}
