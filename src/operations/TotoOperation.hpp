#pragma once

#include "TotoOperationType.hpp"
#include "TotoFileContent.hpp"

struct TotoOperation {
    TotoOperationType type = TotoOperationType::Unknown;
    TotoFileContent contentType = TotoFileContent::Unknown;
    char* inputPath = nullptr;
    char* outputPath = nullptr; 
};