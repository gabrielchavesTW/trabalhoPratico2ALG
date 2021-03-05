#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Data structure to store a graph edge
class Edge
{
public:
    int src, dest;
    Edge(int src, int dest)
    {
        this->src = src;
        this->dest = dest;
    }
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int> > adjList;

    // Graph Constructor
    Graph(vector<Edge> edges, int N)
    {
        // resize the vector to hold `N` elements of type `vector<int>`
        adjList.resize(N);

        // add edges to the undirected graph
        for (int i = 0; i < edges.size(); i++)
        {
            Edge edgeAtual = edges.at(i);
            adjList[edgeAtual.src].push_back(edgeAtual.dest);
            adjList[edgeAtual.dest].push_back(edgeAtual.src);
        }
    }
};

// Node to store vertex and its parent info in BFS
class Node
{
public:
    int v, parent;
    Node(int v, int parent)
    {
        this->v = v;
        this->parent = parent;
    }
};

// Perform BFS on the graph starting from vertex `src` and
// return true if a cycle is found in the graph
bool BFS(Graph const &graph, int src, int N)
{
    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(N);

    // mark the source vertex as discovered
    discovered[src] = true;

    // create a queue for doing BFS and
    // enqueue source vertex
    queue<Node> q;
    q.push(Node(src, -1));

    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and print it
        Node node = q.front();
        q.pop();

        for (int i = 0; i < graph.adjList[node.v].size(); i++)
        {
            int u = graph.adjList[node.v].at(i);
            if (!discovered[u])
            {
                // mark it as discovered
                discovered[u] = true;

                // construct the queue node containing info
                // about vertex and enqueue it
                q.push(Node(u, node.v));
            }

            // `u` is discovered, and `u` is not a parent
            else if (u != node.parent)
            {
                // we found a cross-edge, i.e., the cycle is found
                return true;
            }
        }
    }

    // no cross-edges were found in the graph
    return false;
}

int main()
{
    // initialize edges as per the above diagram
    vector<Edge> edges;
    edges.push_back(Edge(2, 4));
    edges.push_back(Edge(2, 3));
    edges.push_back(Edge(4, 3));

    // total number of nodes in the graph
    int N = 5;

    // build a graph from the given edges
    Graph graph(edges, N);

    // Perform BFS traversal in connected components of a graph
    if (BFS(graph, 1, N))
    {
        cout << "The graph contains a cycle";
    }
    else
    {
        cout << "The graph doesn't contain any cycle";
    }

    return 0;
}