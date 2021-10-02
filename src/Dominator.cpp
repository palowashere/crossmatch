#include "Dominator.hpp"

namespace crossmatch 
{
    Dominator::Dominator(Graph &graph, Graph::Addr vertex)
        : m_graph{graph}
    {
        Algorithm(vertex);
    }

    void Dominator::Algorithm(Graph::Addr vertex)
    {
        for(const auto &p : m_graph)
        {
            m_semi[p.first] = 0;
            m_pred.insert({p.first, std::set<Graph::Addr>{}});
            m_bucket.insert({p.first, std::set<Graph::Addr>{}});
        }

        DepthFirstSearch(vertex);

        for(std::size_t i = m_N; i>= 2; i--)
        {
            const auto w = m_vertex[i];
            for(auto v : m_pred[w])
            {
                m_semi[w] = std::min(m_semi[Evaluate(v)], m_semi[w]);
            }

            m_bucket[m_vertex[m_semi[w]]].insert(w);
            Link(m_parent[w], w);

            auto new_bucket = m_bucket[m_parent[w]];
            for(auto v : m_bucket[m_parent[w]])
            {
                new_bucket.erase(v);
                const auto u = Evaluate(v);
                m_dom[v] = m_semi[u] < m_semi[v] ? u : m_parent[w];
            }

            m_bucket[m_parent[w]] = std::move(new_bucket);
        }

        for(std::size_t i = 2; i < m_N; ++i)
        {
            if(const auto w = m_vertex[i]; m_dom[w] != m_vertex[m_semi[w]])
            {
                m_dom[w] = m_dom[m_dom[w]];
            }
        }
    }

    void Dominator::DepthFirstSearch(Graph::Addr vertex)
    {
        m_semi[vertex] = ++m_N;
        m_vertex[m_N] = vertex;
        m_label[vertex] = vertex;
        m_ancestor[vertex] = 0;

        for(const auto &v : m_graph[vertex])
        {
            if(m_semi[v] == 0)
            {
                m_parent[v] = vertex;
                DepthFirstSearch(v);
            }

            m_pred[v].insert(vertex);
        }
    }

    Graph::Addr Dominator::Evaluate(Graph::Addr vertex)
    {
        if(!m_ancestor[vertex])
        {
            return vertex;
        }
        else
        {
            Compress(vertex);
            return m_label[vertex];
        }
    }

    void Dominator::Compress(Graph::Addr vertex)
    {
        if(!m_ancestor[m_ancestor[vertex]])
        {
            return;
        }

        Compress(m_ancestor[vertex]);

        if(m_semi[m_label[m_ancestor[vertex]]] < m_semi[m_label[vertex]])
        {
            m_label[vertex] = m_label[m_ancestor[vertex]];
        }

        m_ancestor[vertex] = m_ancestor[m_ancestor[vertex]];
    }

    void Dominator::Link(Graph::Addr vertex_a, Graph::Addr vertex_b)
    {
        m_ancestor[vertex_b] = vertex_a;
    }
    
    Graph Dominator::BuildTree() const
    {
        Graph tree;

        for(const auto &p : m_dom)
        {
            tree.AddVertex(p.first);
            tree.AddEdge(p.second, p.first);
        }

        return tree;
    }
}