#include<bits/stdc++.h>
#include<chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;
    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

struct subset
{
    int parent;
    int rank;
};

int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph)
{
 auto start = steady_clock::now();
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    while (e < V - 1)
    {
        struct Edge next_edge = graph->edge[i++];
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        if (x != y)
        {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    auto stop = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << duration.count()<< "ns }";
    int weight=0;
    for (i = 0; i < e; ++i)
    {
        printf("%d -- %d , ", result[i].src, result[i].dest);
        weight+= result[i].weight;
    }
    printf("}%d}", weight);
    return;
}

int minKey(int key[], bool mstSet[],int VERTICES)
{
   int min = INT_MAX, min_index;
   for (int v = 0; v < VERTICES; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
   return min_index;
}

int printMST(int parent[], int n, int graph[100][100])
{
  int weight =0;
   for (int i = 1; i < n; i++)
   {
      printf("%d -- %d ,", i, parent[i]);
weight+= graph[i][parent[i]];
    }
    cout<<"}"<<weight<<"}";
}

void primMST(int graph[100][100],int VERTICES)
{
  auto start = steady_clock::now();

     int parent[VERTICES];
     int key[VERTICES];
     bool mstSet[VERTICES];

     for (int i = 0; i < VERTICES; i++)
        key[i] = INT_MAX, mstSet[i] = false;

     key[0] = 0;
     parent[0] = -1;
     for (int count = 0; count < VERTICES-1; count++)
     {
        int u = minKey(key, mstSet,VERTICES);

        mstSet[u] = true;
        for (int v = 0; v < VERTICES; v++)
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }
     auto stop = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << duration.count()<< "ns }";
     printMST(parent, VERTICES, graph);
}
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);

void boruvkaMST(struct Graph* graph)
{
  auto start = steady_clock::now();
    int V = graph->V, E = graph->E;
    Edge *edge = graph->edge;
    struct subset *subsets = new subset[V];
    int *cheapest = new int[V];
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
        cheapest[v] = -1;
    }
    int numTrees = V;
    int MSTweight = 0;
    while (numTrees > 1)
    {
        for (int i=0; i<E; i++)
        {
            int set1 = find(subsets, edge[i].src);
            int set2 = find(subsets, edge[i].dest);
            if (set1 == set2)
                continue;
            else
            {
               if (cheapest[set1] == -1 ||
                   edge[cheapest[set1]].weight > edge[i].weight)
                 cheapest[set1] = i;

               if (cheapest[set2] == -1 ||
                   edge[cheapest[set2]].weight > edge[i].weight)
                 cheapest[set2] = i;
            }
        }
        for (int i=0; i<V; i++)
        {
            if (cheapest[i] != -1)
            {
                int set1 = find(subsets, edge[cheapest[i]].src);
                int set2 = find(subsets, edge[cheapest[i]].dest);

                if (set1 == set2)
                    continue;
                MSTweight += edge[cheapest[i]].weight;
                printf("%d -- %d ,",
                       edge[cheapest[i]].src, edge[cheapest[i]].dest);
                Union(subsets, set1, set2);
                numTrees--;
            }
        }
    }
    auto stop = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout <<"}"<< duration.count()<< "ns }";
    printf("%d }", MSTweight);
    return;
}
typedef  pair<int, int> iPair;
class GraphC
{
    int V;
    list<int> *adj;
    vector< pair<int, iPair> > edges;
    void DFS(int v, bool visited[]);

public:
    GraphC(int V);
    void addEdge(int u, int v, int w);
    bool isConnected();
    void reverseDeleteMST();
};

GraphC::GraphC(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void GraphC::addEdge(int u, int v, int w)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
    edges.push_back({w, {u, v}});
}

void GraphC::DFS(int v, bool visited[])
{
    visited[v] = true;
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}

bool GraphC::isConnected()
{
    bool visited[V];
    memset(visited, false, sizeof(visited));
    DFS(0, visited);
    for (int i=1; i<V; i++)
        if (visited[i] == false)
            return false;
    return true;
}

void GraphC::reverseDeleteMST()
{
  auto start = steady_clock::now();
    sort(edges.begin(), edges.end());

    int mst_wt = 0;

    for (int i=edges.size()-1; i>=0; i--)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        adj[u].remove(v);
        adj[v].remove(u);
        if (isConnected() == false)
        {
            adj[u].push_back(v);
            adj[v].push_back(u);
            cout <<u<< " -- " << v <<" ,";
            mst_wt += edges[i].first;
        }
    }
    auto stop = steady_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout <<"}"<< duration.count()<< "ns }";
    cout <<mst_wt;
}

int reversedelete(int V,int E,int s[],int d[],int c[])
{
    GraphC g(V);
    for(int i=0;i<E;i++)
    {
      g.addEdge(s[i], d[i], c[i]);
    }

    g.reverseDeleteMST();
    return 0;
}
int boruvka(int V,int E,int s[],int d[],int c[])
{
  struct Graph* graph = createGraph(V, E);
  for(int i=0;i<E;i++)
  {
    graph->edge[i].src = s[i];
    graph->edge[i].dest = d[i];
    graph->edge[i].weight = c[i];
  }

  boruvkaMST(graph);

  return 0;}

int prims(int V,int E,int s[],int d[],int c[])
{
  int temp[100][100];
  for(int i=0;i<V;i++)
    for(int j =0;j<V;j++)
      temp[i][j]=0;
  for(int i=0;i<V;i++)
    for(int j =0;j<V;j++)
        for(int k=0;k<E;k++)
        {
          if(s[k]==i)
            if(d[k]==j)
              temp[i][j]=c[k];
          if(d[k]==i)
            if(s[k]==j)
              temp[i][j]=c[k];
          }
    primMST(temp,V);

    return 0;
}

int krushkal(int V,int E,int s[],int d[],int c[])
{
    struct Graph* graph = createGraph(V, E);
for(int i=0;i<E;i++)
{
  graph->edge[i].src = s[i];
  graph->edge[i].dest = d[i];
  graph->edge[i].weight = c[i];
}
    KruskalMST(graph);

    return 0;
}

int main(){int v = 3;
            int e = 2;
            int s[] ={1,1};
            int d[] = {0,2};
            int c[] = {2,5};krushkal(v,e,s,d,c);
prims(v,e,s,d,c);
boruvka(v,e,s,d,c);
reversedelete(v,e,s,d,c);
}
