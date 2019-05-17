#pragma once

#include "Graph.h"

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial);

template <class T>
void dijkstraShortestPath(Graph<T> * graph, const T &s);
