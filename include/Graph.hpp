#pragma once

#include <map>
#include <vector>
#include <set>

namespace crossmatch
{
    enum class CFGEdgeType 
    {
        None, Jmp, Fallthrough, CallFallthrough
    };

    struct EdgeClass
    {
        size_t tree_edges{0};
        size_t forward_edges{0};
        size_t cross_edges{0};
        size_t back_edges{0};
    };

    class Graph {
    public:
        using Addr = uint64_t;
        using GraphMap = std::map<Addr, std::set<Addr>>;
        using VertexLevels = std::map<Addr, std::size_t>;
        using Visited = std::map<Addr, bool>;
        
        struct EdgeClassHelper 
        {
            Visited visited;
            std::map<Addr, int> num;
            int index{0};
            EdgeClass edge_class;
        };

        void        AddEdge(Addr src_vertex, Addr dst_vertex, CFGEdgeType type = CFGEdgeType::None);
        void        AddEdge(Addr src_vertex, const std::set<Addr> &dst_vec);
        void        AddEdgeType(Addr src_vertex, Addr dst_vertex, CFGEdgeType type);
        CFGEdgeType GetEdgeType(Addr src_vertex, Addr dst_vertex) const;
        bool        AddVertex(Addr vertex);
        void        RemoveVertex(Addr vertex);
        void        RemoveEdge(Addr src_vertex, Addr dst_vertex);
        std::size_t GetMaxDepth(Addr start_vertex) const;
        EdgeClass   GetEdgeClass() const;
        
        std::set<Addr> GetPreds(Addr vertex) const;
        std::set<Addr> GetSuccs(Addr vertex) const;

        std::string GetBitSignature(Addr start_vertex) const;

    private:
        VertexLevels GetVertexLevels(Addr start_vertex) const;
        void         GetBitSignatureInternal(Addr vertex, Visited &visited, std::string &signature) const;
        void         GetEdgeClassInternal(Addr vertex, EdgeClassHelper &helper) const;

    private:
        GraphMap m_graph;
        std::map<Addr, std::map<Addr, CFGEdgeType>> m_edge_types;
    };
}