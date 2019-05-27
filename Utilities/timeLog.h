#pragma once

#include "../Graph/Graph.h"
#include "MapInfo.h"

enum algorithm_t{
	BIDIJKSTRA,
	BIASTAR_EUCLIDIAN,
	BIASTAR_MANHATTAN,
	DIJKSTRA,
	ASTAR_EUCLIDIAN,
	ASTAR_MANHATTAN,
	SCC,
	INVERT_GRAPH,
	FW,
	NNFW,
	NNEUCLIDIAN,
	OPT2,
	_N_ALGORITHM
};

void startTime();

long long getElapsedTimeMiliSeconds();

void writeTime(const algorithm_t& algorithm, Graph<MapInfo> * graph, bool bidirectional);