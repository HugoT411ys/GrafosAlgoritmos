#include <iostream>

#include "..\Data_Structures\Graph.hpp"
#include <queue>

#define blank_line std::cout << std::endl
#define a(i,j) i * g.V + j

const llint INF = 999999999;

inline llint min(llint a, llint b) { return a < b ? a : b; }

void print_arr(llint *a, llint n, std::string s)
{
    llint i;

    std::cout << s << std::endl;
    for (i = 0; i < n-1; ++i)
    {
        std::cout << "| " <<a[i] << " ";
    }
    std::cout << "| " << a[i] << " |" << std::endl;
}

llint bfs(Graph &g, llint s, llint t, llint *cap, llint *par, llint *vis)
{
    llint i, j;
    std::queue<llint> queue;

    queue.push(s);

    while(!queue.empty())
    {
        llint u = queue.front();
        queue.pop();
        
        vis[u] = 1;

        for (edge e : g.vertices[u])
        {
            if (e.vertex == t)
            {
                llint min_edge = INF;
                par[e.vertex] = u;
                while(par[t] != -1)
                {
                    min_edge = min(min_edge, cap[a(par[t], t)]);
                    t = par[t];
                }
                return min_edge;
            }
            if (cap[a(u,e.vertex)] && !vis[e.vertex])
            {
                par[e.vertex] = u;
                queue.push(e.vertex);
            }
        }
    }
    return 0;
}

llint max_flow(Graph &g, llint src, llint tar)
{
    llint i;
    llint *cap, *par, *vis;
    llint f, max_f;

    cap = new llint[g.V * g.V];
    par = new llint[g.V];
    vis = new llint[g.V];

    for (i = 0; i < g.V; i++)
    {
        par[i] = -1, vis[i] = 0;
        for (edge e : g.vertices[i])
        {
            cap[a(i,e.vertex)] = e.weight;
        }
    }

    max_f = 0;
    while (f = bfs(g, src, tar, cap, par, vis))
    {
        i = tar;
        while(par[i] != -1)
        {
            cap[a(par[i], i)] -= f;
            i = par[i];
        }
        max_f += f;
        for (i = 0; i < g.V; i++)
        {
            vis[i] = 0;
            par[i] = -1;
        }
    }
    return max_f;
}

int main(int argc, char const *argv[])
{
    llint i;
    llint num_ver, num_edges;

    std::cin >> num_ver >> num_edges;

    Graph graph(num_ver);
    llint source, target, weight;

    for (i = 0; i < num_edges; i++)
    {
        std::cin >> source >> target >> weight;
        graph.add_edge(source, target, weight);
    }

    std::cout << "Input Graph:" << std::endl;
    graph.print();
    blank_line;

    std::cout << "Maximum Flow from source (0) to sink (" << graph.V - 1 << "):" << std::endl;
    std::cout << max_flow(graph, 0, graph.V - 1) << std::endl;
    
    return 0;
}