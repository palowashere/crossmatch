#pragma once

#include <retdec/common/function.h>

#include "StructuralInfo.hpp"
#include "Function.hpp"

namespace crossmatch
{
    class StructuralAnalysis {
    public:
        bool Analyze(Function &f, const retdec::common::Function &function);
    };
}