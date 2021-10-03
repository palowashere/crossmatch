#include "StructuralAnalysis.hpp"
#include "Log.hpp"

namespace crossmatch
{
    bool StructuralAnalysis::Analyze(Program &program, const retdec::common::Function &function)
    {
        log->debug("[StructuralAnalysis::Analyze] Structural analysis of function '%s'", function.getName().c_str());

        if(const auto &basic_blocks = function.basicBlocks; basic_blocks.size() > MaxNumOfBBs)
        {
            log->info("[StructuralAnalysis::Analyze] Skipping function '%s' because it has %d bbs", function.getName().c_str(), basic_blocks.size());
            return false;
        }

        // TODO
        (void) program;

        return true;
    }
}