#include <stdio.h>
#include <iostream>

#include "./operations/TotoOperation.hpp"
#include "./operations/TotoOperationHandler.hpp"

using namespace std;


TotoOperation createOperationFromArguments(int argc, char** argv);

int main(int argc, char** argv) {
    TotoOperation operation = createOperationFromArguments(argc, argv);
    
    TotoOperationHandler(operation)
        .execute();

    return 0;
}

// TODO : What if no arguments ? -> ask for operation todo
TotoOperation createOperationFromArguments(int argc, char** argv) {
    TotoOperation operation;

    if (argc == 1) {
        operation.type = TotoOperationType::PrintHelp;
        return operation;
    }

    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            operation.type = TotoOperationType::PrintHelp;
        } else {
            throw runtime_error("Unknown command.");
        }

        return operation;
    }

    operation.inputPath = argv[2];

    if (strcmp(argv[1], "--compress") == 0) {
        operation.type = TotoOperationType::Compress;
    } else if (strcmp(argv[1], "--decompress") == 0) {
        operation.type = TotoOperationType::Decompress;
    } else {
        throw runtime_error("Unknown command.");
    }

    if (argc != 5) {
        return operation;
    }

    if (strcmp(argv[3], "-o") == 0) {
        operation.outputPath = argv[4];
    } else {
        throw runtime_error("Unknown command.");
    }

    return operation;
}
