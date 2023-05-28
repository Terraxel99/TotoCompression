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
    switch (this->operation.contentType) {
        case TotoFileContent::Image:
            this->executeImageCompressionOperation();
            break;
        
        case TotoFileContent::IFrameOnlyVideo:
            this->executeIFrameOnlyVideoCompressionOperation();
            break;

        case TotoFileContent::Unknown:
        default:
            throw runtime_error("Unsupported");
            break;
    }
}

void TotoOperationHandler::executeImageCompressionOperation() {
    TotoImage image = TotoImage::fromFile(this->operation.inputPath, false);
    image.compress(true);

    image.save(this->operation.outputPath);
}

void TotoOperationHandler::executeIFrameOnlyVideoCompressionOperation() {
    TotoIVideo video = TotoIVideo::fromFile(this->operation.inputPath);
    video.compress();
}

void TotoOperationHandler::executeDecompressionOperation() {
    switch (this->operation.contentType) {
        case TotoFileContent::Image:
            this->executeImageDecompressionOperation();
            break;
        
        case TotoFileContent::IFrameOnlyVideo:
            this->executeIFrameOnlyVideoDecompressionOperation();
            break;

        case TotoFileContent::Unknown:
        default:
            throw runtime_error("Unsupported");
            break;
    }
}

void TotoOperationHandler::executeImageDecompressionOperation() {
    TotoImage image = TotoImage::fromFile(this->operation.inputPath, true);

    image.decompress(true);

    image.save(this->operation.outputPath);
}

void TotoOperationHandler::executeIFrameOnlyVideoDecompressionOperation() {
    TotoIVideo video = TotoIVideo::fromFile(this->operation.inputPath);
    video.decompress();
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
