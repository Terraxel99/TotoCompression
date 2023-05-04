#pragma once

#include "TotoOperationType.hpp"

struct TotoOperation {
    TotoOperationType type = TotoOperationType::Unknown;
    char* inputPath = nullptr;
    char* outputPath = nullptr; // Optional -> Will have a default name when not set.
};