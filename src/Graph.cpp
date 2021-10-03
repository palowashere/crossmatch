#include "Graph.hpp"

#include <queue>

namespace crossmatch
{
    void Graph::AddEdge(const Addr &src_vertex, const Addr &dst_vertex, CFGEdgeType type)
    {
        if(!m_graph.count(src_vertex))
        {
            AddVertex(src_vertex);
        }

        AddVertex(dst_vertex);
        m_graph[src_vertex].insert(dst_vertex);
        AddEdgeType(src_vertex, dst_vertex, type);
    }

    void Graph::AddEdge(const Addr &src_vertex, const std::set<Addr> &dst_vec)
    {
        if(!m_graph.count(src_vertex))
        {
            AddVertex(src_vertex);
        }

        for(const auto &dst : dst_vec)
        {
            AddVertex(dst);
            m_graph[src_vertex].insert(dst);
        }
    }

    void Graph::AddEdgeType(const Addr &src_vertex, const Addr &dst_vertex, CFGEdgeType type)
    {
        if(!m_graph.count(src_vertex))
        {
            m_edge_types[src_vertex] = {};   
        }

        m_edge_types[src_vertex][dst_vertex] = type;
    }

    CFGEdgeType Graph::GetEdgeType(const Addr &src_vertex, const Addr &dst_vertex) const
    {
        if(!m_edge_types.count(src_vertex) || !m_edge_types.at(src_vertex).count(dst_vertex))
        {
            return CFGEdgeType::None;
        }
        else
        {
            return m_edge_types.at(src_vertex).at(dst_vertex);
        }
    } 

    bool Graph::AddVertex(const Addr &vertex)
    {
        if(m_graph.count(vertex))
        {
            return false;
        }
        else
        {
            m_graph.insert({vertex, std::set<Addr>{}});
            return true;
        }
    }

    void Graph::RemoveVertex(const Addr &vertex)
    {
        m_graph.erase(vertex);
    }

    void Graph::RemoveEdge(const Addr &src_vertex, const Addr &dst_vertex)
    {
        if(m_graph.count(src_vertex) && m_graph.at(src_vertex).count(dst_vertex))
        {
            m_graph.at(src_vertex).erase(dst_vertex);
            m_edge_types.at(src_vertex).erase(dst_vertex);
        }
    }

    Graph::VertexLevels Graph::GetVertexLevels(const Addr &start_vertex) const
    {
        Visited visited;
        std::queue<Addr> queue;
        VertexLevels levels;

        for(const auto &v : m_graph)
        {
            levels[v.first] = 0;
        }

        queue.push(start_vertex);
        levels[start_vertex] = 0;
        levels[start_vertex] = true;

        while(!queue.empty())
        {
            auto vertex = queue.front();
            queue.pop();
            
            for(const auto &v : m_graph.at(vertex))
            {
                if(!visited[v])
                {
                    queue.push(v);
                    levels[v] = levels[vertex] + 1;
                    visited[v] = true;
                }
            }
        }

        return levels;
    }

    std::size_t Graph::GetMaxDepth(const Addr &start_vertex) const
    {
        std::size_t depth{0};

        // TODO: std::sort?
        for(const auto &v : GetVertexLevels(start_vertex))
        {
            if(v.second > depth)
            {
                depth = v.second;
            }
        }

        return depth;
    }

    std::set<Addr> Graph::GetPreds(const Addr &vertex) const
    {
        std::set<Addr> preds;
        
        for(const auto &v : m_graph)
        {
            if(v.second.count(vertex))
            {
                preds.insert(v.first);
            }
        }
        
        return preds;
    }

    std::set<Addr> Graph::GetSuccs(const Addr &vertex) const
    {
        if(!m_graph.count(vertex))
        {
            return {};
        }
        else
        {
            return m_graph.at(vertex);
        }
    }

    std::string Graph::GetBitSignature(const Addr &start_vertex) const
    {
        if(!m_graph.count(start_vertex))
        {
            return "";
        }

        Visited visited;
        std::string signature;
        signature.reserve(m_graph.size() * 2);
        GetBitSignatureInternal(start_vertex, visited, signature);

        return signature;
    }

    void Graph::GetBitSignatureInternal(const Addr &vertex, Visited &visited, std::string &signature) const
    {
        visited[vertex] = true;
        signature += "1";

        for(const auto &v : m_graph.at(vertex))
        {
            if(!visited[v])
            {
                GetBitSignatureInternal(v, visited, signature);
            }
        }

        signature += "0";
    }

    EdgeClass Graph::GetEdgeClass() const
    {
        EdgeClassHelper helper;

        for(const auto &v : m_graph)
        {
            if(helper.num[v.first] == 0)
            {
                GetEdgeClassInternal(v.first, helper);
            }
        }

        return helper.edge_class;
    }

    void Graph::GetEdgeClassInternal(const Addr &vertex, EdgeClassHelper &helper) const
    {
        helper.num[vertex] = helper.index++;
        helper.visited[vertex] = true;

        for(const auto &v : m_graph.at(vertex))
        {
            if(helper.num[v] == 0)
            {
                helper.edge_class.tree_edges++;
                GetEdgeClassInternal(v, helper);
            }
            else if(helper.num[v] > helper.num[vertex])
            {
                helper.edge_class.forward_edges++;
            }
            else if(!helper.visited[v])
            {
                helper.edge_class.cross_edges++;
            }
            else
            {
                helper.edge_class.back_edges++;
            }
        }
    }

    Graph::GraphMap::iterator Graph::begin()
    {
        return m_graph.begin();
    }

    Graph::GraphMap::iterator Graph::end()
    {
        return m_graph.end();
    }

    Graph::GraphMap::const_iterator Graph::begin() const
    {
        return m_graph.begin();
    }

    Graph::GraphMap::const_iterator Graph::end() const
    {
        return m_graph.end();
    }

    std::size_t Graph::size() const
    {
        return m_graph.size();
    }
    
    const std::set<Addr>& Graph::operator[](Addr vertex) const
    {
        return m_graph.at(vertex);
    }

    bool Graph::HasVertex(const Addr &vertex) const
    {
        return m_graph.count(vertex);
    }
}