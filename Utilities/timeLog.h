#pragma once

#include "../Graph/Graph.h"
#include "MapInfo.h"

enum algorithm_t{
	BIDIJKSTRA,
	BIASTAR_EUCLIDIAN,
	DIJKSTRA,
	ASTAR_EUCLIDIAN,
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