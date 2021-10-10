#pragma once

#include "StructuralInfo.hpp"
#include "Function.hpp"
#include "Program.hpp"

namespace crossmatch
{
    class StructuralAnalysis {
    public:
        bool Analyze(Program &program, const llvm::Function &function, llvm::CallGraph &callgraph);

    private:
        int GetCallgraphDepth(const llvm::Function &function, llvm::CallGraph &callgraph) const;
    };
}