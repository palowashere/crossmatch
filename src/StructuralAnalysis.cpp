#include "StructuralAnalysis.hpp"
#include "Log.hpp"

namespace crossmatch
{
    bool StructuralAnalysis::Analyze(Function &f, const retdec::common::Function &function)
    {
        StructuralInfo info;
        log->debug("[StructuralAnalysis::Analyze] Structural analysis of function '%s'", f.GetName().c_str());

        const auto &basic_blocks = function.basicBlocks;

        if(basic_blocks.size() > MaxNumOfBBs)
        {
            log->info("[StructuralAnalysis::Analyze] Skipping function '%s' because it has %d bbs", f.GetName().c_str(), basic_blocks.size());
            return false;
        }

        info.bb_count = basic_blocks.size();

        return true;
    }
}