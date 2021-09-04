#include "dijkstra_algorithm.h"

Dijkstra::Dijkstra(int **_edges, int _n)
{
    this->graph = _edges;
    this->V = _n;
}



int Dijkstra::minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = 90000, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void Dijkstra::printSolution(int dist[]){
    qDebug() << "Vertex \t\t Distance from Source\n";
    for (int i = 0; i < V; i++)
        qDebug() << i << " " << dist[i];
}

void Dijkstra::_finding(int src, int _end){

       int *dist = new int[V]; // The output array.  dist[i] will hold the shortest
       // distance from src to i

       bool *sptSet = new bool[V]; // sptSet[i] will be true if vertex i is included in shortest
       // path tree or shortest distance from src to i is finalized

       // Initialize all distances as INFINITE and stpSet[] as false
       for (int i = 0; i < V; i++)
           dist[i] = 90000, sptSet[i] = false;

       // Distance of source vertex from itself is always 0
       dist[src] = 0;

       // Find shortest path for all vertices
       for (int count = 0; count < V - 1; count++) {
           // Pick the minimum distance vertex from the set of vertices not
           // yet processed. u is always equal to src in the first iteration.
           int u = minDistance(dist, sptSet);

           // Mark the picked vertex as processed
           sptSet[u] = true;

           // Update dist value of the adjacent vertices of the picked vertex.
           for (int v = 0; v < V; v++)

               // Update dist[v] only if is not in sptSet, there is an edge from
               // u to v, and total weight of path from src to  v through u is
               // smaller than current value of dist[v]
               if (!sptSet[v] && graph[u][v] && dist[u] != 90000
                   && dist[u] + graph[u][v] < dist[v])
                   dist[v] = dist[u] + graph[u][v];
       }


       int end = _end, start = src, weight = dist[end];
       while(end != start){

           for(int i = 0; i < V; i++){

               if(graph[i][end] != 0){

                   int temp = weight - graph[i][end];
                   if(temp == dist[i]){
                       weight = temp;
                       end = i;
                       way.push_back(i);
                   }
               }
           }
       }

       reverse(way.begin(), way.end());
       way.push_back(_end);

       for(int i = 0; i < V; i++){
           _dist.push_back(dist[i]);
       }
       // print the constructed distance array
       qDebug() << "HERE";
       for (int i = 0; i < way.size(); i++)
           qDebug() << way[i];
       qDebug() << "____________";
       qDebug() << "____________";
       printSolution(dist);
}

vector<int> Dijkstra::get_way(){
    return way;
}
vector<int> Dijkstra::get_dist(){
    return _dist;
}
