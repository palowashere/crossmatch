#pragma once

#include <retdec/common/function.h>

#include "StructuralInfo.hpp"
#include "Function.hpp"
#include "Program.hpp"

namespace crossmatch
{
    class StructuralAnalysis {
    public:
        bool Analyze(Program &program, const retdec::common::Function &function);
    };
}