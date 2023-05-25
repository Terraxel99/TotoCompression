#include <stdio.h>
#include <iostream>

#include "./operations/TotoOperation.hpp"
#include "./operations/TotoOperationHandler.hpp"

using namespace std;


TotoOperation createOperationFromArguments(int argc, char** argv);
TotoFileContent getContentTypeFromArgument(char* arg);

int main(int argc, char** argv) {
    TotoOperation operation = createOperationFromArguments(argc, argv);

    try {
        TotoOperationHandler(operation)
            .execute();
    } catch (std::exception& e) {
        cerr << "An error occured : " << endl << endl << e.what() << endl << endl;
        cerr << "Terminating" << endl;

        return 1;
    }

    return 0;
}

TotoOperation createOperationFromArguments(int argc, char** argv) {
    TotoOperation operation;

    if (argc == 1) {
        operation.type = TotoOperationType::PrintHelp;
        return operation;
    }

    if (strcmp(argv[1], "--help") == 0) {
        operation.type = TotoOperationType::PrintHelp;
    }

    if (strcmp(argv[1], "--compress") == 0) {
        operation.type = TotoOperationType::Compress;
        operation.contentType = getContentTypeFromArgument(argv[2]);
        operation.inputPath = argv[3];
        operation.outputPath = argv[4];
    }

    if (strcmp(argv[1], "--decompress") == 0) {
        operation.type = TotoOperationType::Decompress;
        operation.contentType = getContentTypeFromArgument(argv[2]);
        operation.inputPath = argv[3];
        operation.outputPath = argv[4];
    }

    if (strcmp(argv[1], "--psnr") == 0) {
        operation.type = TotoOperationType::PSNR;
        operation.inputPath = argv[2];
        operation.outputPath = argv[3];
    }

    return operation;
}

TotoFileContent getContentTypeFromArgument(char* arg) {
    if (strcmp(arg, "--image") == 0) {
        return TotoFileContent::Image;
    }

    if (strcmp(arg, "--video") == 0) {
        return TotoFileContent::IFrameOnlyVideo;
    }

    return TotoFileContent::Unknown;
}
