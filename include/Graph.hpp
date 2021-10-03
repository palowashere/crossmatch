#pragma once

#include <map>
#include <vector>
#include <set>

#include "Utility.hpp"

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
        using GraphMap = std::map<Addr, std::set<Addr>>;
        using VertexLevels = std::map<Addr, std::size_t>;
        using Visited = std::map<Addr, bool>;

        Graph() = default;
        
        struct EdgeClassHelper 
        {
            Visited visited;
            std::map<Addr, int> num;
            int index{0};
            EdgeClass edge_class;
        };

        const std::set<Addr>& operator[](Addr vertex) const;

        GraphMap::iterator begin();
        GraphMap::iterator end();
        GraphMap::const_iterator begin() const;
        GraphMap::const_iterator end() const;
        std::size_t size() const;

        void        AddEdge(const Addr &src_vertex, const Addr &dst_vertex, CFGEdgeType type = CFGEdgeType::None);
        void        AddEdge(const Addr &src_vertex, const std::set<Addr> &dst_vec);
        void        AddEdgeType(const Addr &src_vertex, const Addr &dst_vertex, CFGEdgeType type);
        CFGEdgeType GetEdgeType(const Addr &src_vertex, const Addr &dst_vertex) const;
        bool        AddVertex(const Addr &vertex);
        void        RemoveVertex(const Addr &vertex);
        void        RemoveEdge(const Addr &src_vertex, const Addr &dst_vertex);
        std::size_t GetMaxDepth(const Addr &start_vertex) const;
        EdgeClass   GetEdgeClass() const;
        bool        HasVertex(const Addr &vertex) const;
        
        std::set<Addr> GetPreds(const Addr &vertex) const;
        std::set<Addr> GetSuccs(const Addr &vertex) const;

        std::string GetBitSignature(const Addr &start_vertex) const;

    private:
        VertexLevels GetVertexLevels(const Addr &start_vertex) const;
        void         GetBitSignatureInternal(const Addr &vertex, Visited &visited, std::string &signature) const;
        void         GetEdgeClassInternal(const Addr &vertex, EdgeClassHelper &helper) const;

    private:
        GraphMap m_graph;
        std::map<Addr, std::map<Addr, CFGEdgeType>> m_edge_types;
    };
}