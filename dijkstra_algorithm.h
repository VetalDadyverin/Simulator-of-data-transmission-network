#ifndef DIJKSTRA_ALGORITHM_H
#define DIJKSTRA_ALGORITHM_H
#include "widget.h"
#include <vector>
#include <algorithm>
using namespace std;

class Dijkstra
{
public:
    Dijkstra(int **_edge, int _V);
    ~Dijkstra();
    void _finding(int src,int _end);
    int minDistance(int dist[], bool sptSet[]);
    void printSolution(int dist[]);
    vector<int> get_way();
    vector<int> get_dist();
private:
    int **graph;
    int V;
    vector<int> way;
    vector<int> _dist;
};

#endif // DIJKSTRA_ALGORITHM_H
