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
        size_t tree_edges;
        size_t forward_edges;
        size_t cross_edges;
        size_t back_edges;
    };

    struct StructuralInfo 
    {
        std::size_t bb_count;
        std::size_t folded_bb_count;
        std::size_t entry_points;
        std::size_t exit_points;
        std::size_t inlinks;
        std::size_t unique_inlinks;
        std::size_t outlinks;
        std::size_t unique_outlinks;
        EdgeClass edge_class;
        std::size_t scc;
        std::size_t self_loops;
        std::size_t scc_loops;
        std::string cfg_dfs_bitsig;
        std::string dom_dfs_bitsig;
        std::string folded_dfs_bitsig;
        std::string folded_dom_dfs_bitsig;
        unsigned cyc_complexity;
        CyclomaticComplexity cyc_complexity_range;
        int callgraph_depth;
        int callgraph_dom_depth;
        std::size_t depth;
    };

    // TODO: weights
}