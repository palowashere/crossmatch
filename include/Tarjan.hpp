#pragma once

#include "Graph.hpp"

namespace crossmatch
{
    class Tarjan {
    public:
        using Components = std::vector<Graph::Addr>;

        explicit Tarjan(Graph &graph);

        std::vector<Components> GetSCC();

    private:
        void Visit(std::vector<Components> &result, Graph::Addr vertex);

    private:
        Graph &m_graph;
        std::map<Graph::Addr, std::size_t> m_low;
        std::vector<Graph::Addr> m_stack;
    };
}