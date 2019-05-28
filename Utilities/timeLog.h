#pragma once

#include "../Graph/Graph.h"
#include "MapInfo.h"

/**
 * @brief Enum with the different types of algorithm
 * 
 */
enum algorithm_t{
	DFS,
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

/**
 * @brief Function that starts the clock
 * 
 */
void startTime();

/**
 * @brief Get the Elapsed Time Miliseconds since the startTime fuction
 * 
 * @return long long Elapsed Time Miliseconds
 */
long long getElapsedTimeMiliSeconds();

/**
 * @brief Writes to times.csv file in a formatted way
 * 
 * @param algorithm Type od the algorithm corresponding to an enum value
 * @param graph Graph where the algorithm was run so we can get the number of edged, the number of vertexes and other usefull information
 * @param bidirectional Whether the graph is Directed or not
 */
void writeTime(const algorithm_t& algorithm, Graph<MapInfo> * graph, bool bidirectional);