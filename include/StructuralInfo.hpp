#pragma once

#include <string>
#include <map>

namespace crossmatch
{
    // constants
    const std::size_t MaxNumOfBBs = 1000;

    enum class CyclomaticComplexity : unsigned
    {
        Normal = 11,    // >= 0  && < 11 -> normal
        Moderate = 21,  // >= 11 && < 21 -> moderate
        Risky = 40,     // >= 21 && < 41 -> risky
        Unstable = 41   // >= 40 -> unstable
    };

    enum class CFGEdgeType 
    {
        None, Jmp, Fallthrough, CallFallthrough
    };

    // TODO: move to Graph class?
    struct EdgeClass
    {
        size_t tree_edges{0};
        size_t forward_edges{0};
        size_t cross_edges{0};
        size_t back_edges{0};
    };

    struct StructuralInfo 
    {
        std::size_t bb_count{0};
        std::size_t folded_bb_count{0};
        std::size_t entry_points{0};
        std::size_t exit_points{0};
        std::size_t inlinks{0};
        std::size_t unique_inlinks{0};
        std::size_t outlinks{0};
        std::size_t unique_outlinks{0};
        EdgeClass edge_class;
        std::size_t scc{0};
        std::size_t self_loops{0};
        std::size_t scc_loops{0};
        std::string cfg_dfs_bitsig{""};
        std::string dom_dfs_bitsig{""};
        std::string folded_dfs_bitsig{""};
        std::string folded_dom_dfs_bitsig{""};
        unsigned cyc_complexity{0};
        CyclomaticComplexity cyc_complexity_range;
        int callgraph_depth{0};
        int callgraph_dom_depth{0};
        std::size_t depth{0};
    };

    // loaded from configuration file
    struct StructuralWeights
    {
        std::size_t bb_count{0};
        std::size_t entry_points{0};
        std::size_t exit_points{0};
        std::size_t inlinks{0};
        std::size_t unique_inlinks{0};
        std::size_t outlinks{0};
        std::size_t unique_outlinks{0};
        std::size_t loops{0};
        std::size_t forward_edges{0};
        std::size_t cross_edges{0};
        std::size_t back_edges{0};
        std::size_t basis_edges{0};
        std::size_t cfg_bitsig{0};
        std::size_t folded_cfg_bitsig{0};
        std::size_t dom_bitsig{0};
        std::size_t folded_dom_bitsig{0};
        std::size_t cyc_complexity{0};
        std::size_t callgraph_depth{0};
        std::size_t callgraph_dom_depth{0};
    };
}