#pragma once

#include "Graph.hpp"

namespace crossmatch
{
    class Tarjan {
    public:
        using Components = std::vector<Addr>;

        explicit Tarjan(Graph &graph);

        std::vector<Components> GetSCC();

    private:
        void Visit(std::vector<Components> &result, const Addr &vertex);

    private:
        Graph &m_graph;
        std::map<Addr, std::size_t> m_low;
        std::vector<Addr> m_stack;
    };
}