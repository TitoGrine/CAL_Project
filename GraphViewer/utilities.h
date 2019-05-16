#pragma once

#include "graphviewer.h"
#include <string>
#include "../Graph/Graph.h"

GraphViewer * createVertexGraphViewer(const Graph * graph, int vertexSize, std::string vertexColor);

void addEdgesToGV(const Graph * graph, GraphViewer * gv);

GraphViewer * createFullGraphViewer(const Graph * graph, int vertexSize, std::string vertexColor);