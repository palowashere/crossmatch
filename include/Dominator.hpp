#pragma once

#include <functional>

#include "Graph.hpp"

namespace crossmatch
{
    class Dominator {
    public:
        Dominator(Graph &graph, Graph::Addr vertex);
        Dominator(const Dominator&) = delete;
        Dominator &operator=(const Dominator&) = delete;

        Graph BuildTree() const;

    private:
        void        Algorithm(Graph::Addr vertex);
        void        DepthFirstSearch(Graph::Addr vertex);
        Graph::Addr Evaluate(Graph::Addr vertex);
        void        Compress(Graph::Addr vertex);
        void        Link(Graph::Addr vertex_a, Graph::Addr vertex_b);

    private:
        Graph::GraphMap m_bucket;
        Graph::GraphMap m_pred;
        std::map<Graph::Addr, Graph::Addr> m_label;
        std::map<Graph::Addr, Graph::Addr> m_parent;
        std::map<Graph::Addr, Graph::Addr> m_ancestor;
        std::map<Graph::Addr, Graph::Addr> m_dom;
        std::map<Graph::Addr, std::size_t> m_semi;
        std::map<std::size_t, Graph::Addr> m_vertex;
        std::size_t m_N{0};
        Graph &m_graph;
    };
}