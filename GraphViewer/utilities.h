#pragma once

#include "graphviewer.h"
#include <string>
#include "../Graph/Graph.h"

template <class T>
GraphViewer * createVertexGraphViewer(const Graph<T> * graph, int vertexSize, std::string vertexColor);

template <class T>
void addEdgesToGV(const Graph<T> * graph, GraphViewer * gv);

template <class T>
GraphViewer * createFullGraphViewer(const Graph<T> * graph, int vertexSize, std::string vertexColor);

template <class T>
void paintVertexesGV(GraphViewer * gv, int vertexSize, std::string vertexColor, const std::vector<Vertex<T> *> & vertexes);