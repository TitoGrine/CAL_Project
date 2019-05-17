#pragma once

#include "Graph.h"

std::vector<Vertex *> dfs(Graph * graph, Vertex * initial);

std::vector<Vertex *> scc(Graph * graph, Vertex * initial);

void dijkstraShortestPath(Graph * graph, const long &s);
