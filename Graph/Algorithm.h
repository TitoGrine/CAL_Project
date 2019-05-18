#pragma once

#include "Graph.h"

std::vector<Vertex *> dfs(Graph * graph, Vertex * initial);

std::vector<Vertex *> scc(Graph * graph, Vertex * initial);

std::vector<long> dijkstraShortestPath(Graph * graph, const long &origin, const long &dest);

std::vector<long> aStarShortestPath(Graph * graph, const long &origin, const long &dest);

std::vector<long> bidirectionalDijkstra(Graph * graph, const long &origin, const long &delivery, const long &dest);

std::vector<long> bidirectionalAStar(Graph * graph, const long &origin, const long &delivery, const long &dest);