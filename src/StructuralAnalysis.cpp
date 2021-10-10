#include "StructuralAnalysis.hpp"
#include "Log.hpp"

#include <llvm/IR/Function.h>
#include <llvm/ADT/DepthFirstIterator.h>

namespace crossmatch
{
    bool StructuralAnalysis::Analyze(Program &program, const llvm::Function &function, llvm::CallGraph &callgraph)
    {
        StructuralInfo si;

        log->debug("[StructuralAnalysis::Analyze] Structural analysis of function '%s'", function.getName().data());

        if(const auto &basic_blocks = function.getBasicBlockList(); basic_blocks.size() > MaxNumOfBBs)
        {
            log->info("[StructuralAnalysis::Analyze] Skipping function '%s' because it has %d bbs", function.getName().data(), basic_blocks.size());
            return false;
        }

        (void)program;

        si.callgraph_depth = GetCallgraphDepth(function, callgraph);

        return true;
    }

    int StructuralAnalysis::GetCallgraphDepth(const llvm::Function &function, llvm::CallGraph &callgraph) const
    {
        for(auto it = llvm::df_begin(&callgraph); it != llvm::df_end(&callgraph); it++)
        {
            if(auto f = it->getFunction(); f && f->getName().equals(function.getName()))
            {
                auto depth = it.getPathLength();
                log->debug("[StructuralAnalysis::GetCallgraphDepth] Function '%s' depth: %d", f->getName().data(), depth);
                return depth;
            }
        }

        return -1;
    }
}