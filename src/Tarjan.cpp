#include "Tarjan.hpp"

namespace crossmatch
{
    Tarjan::Tarjan(Graph &graph)
        : m_graph{graph}
    {
        
    }

    std::vector<Tarjan::Components> Tarjan::GetSCC()
    {
        std::vector<Components> result;

        for(const auto &p : m_graph)
        {
            Visit(result, p.first);
        }

        return result;
    }

    void Tarjan::Visit(std::vector<Components> &result, Graph::Addr vertex)
    {
        if(m_low.count(vertex))
        {
            return;
        }

        if(!m_graph.HasVertex(vertex))
        {
            m_graph.AddVertex(vertex);
        }

        auto num = m_low.size();
        m_low[vertex] = num;

        auto stack_pos = m_stack.size();
        m_stack.push_back(vertex);

        for(auto succ : m_graph[vertex])
        {
            Visit(result, succ);
            m_low[vertex] = std::min(m_low[vertex], m_low[succ]);
        }

        if(num == m_low[vertex])
        {
            Components component(m_stack.begin() + stack_pos, m_stack.end());
            m_stack.erase(m_stack.begin() + stack_pos, m_stack.end());
            result.push_back(component);

            for(const auto &item : component)
            {
                m_low[item] = m_graph.size();
            }
        }
    }
}