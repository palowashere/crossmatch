#pragma once

#include <functional>

#include "Graph.hpp"

namespace crossmatch
{
    class Dominator {
    public:
        Dominator(Graph &graph, const Addr &vertex);
        Dominator(const Dominator&) = delete;
        Dominator &operator=(const Dominator&) = delete;

        Graph BuildTree() const;

    private:
        void Algorithm(const Addr &vertex);
        void DepthFirstSearch(const Addr &vertex);
        Addr Evaluate(const Addr &vertex);
        void Compress(const Addr &vertex);
        void Link(const Addr &vertex_a, const Addr &vertex_b);

    private:
        Graph::GraphMap m_bucket;
        Graph::GraphMap m_pred;
        std::map<Addr, Addr> m_label;
        std::map<Addr, Addr> m_parent;
        std::map<Addr, Addr> m_ancestor;
        std::map<Addr, Addr> m_dom;
        std::map<Addr, std::size_t> m_semi;
        std::map<std::size_t, Addr> m_vertex;
        std::size_t m_N{0};
        Graph &m_graph;
    };
}