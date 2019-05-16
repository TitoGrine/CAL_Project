/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "Vertex.h"
#include "Edge.h"
#include "../Utilities/MutablePriorityQueue.h"

using namespace std;

class Edge;
class Graph;
class Vertex;

#define INF std::numeric_limits<double>::max()


/*************************** Graph  **************************/

class Graph {
	vector<Vertex *> vertexSet;    // vertex set

	double rightBound, leftBound, topBound, bottomBound;

	// Fp05
	Vertex * initSingleSource(const long &orig);
	bool relax(Vertex *v, Vertex *w, double weight);
	double ** W = nullptr;   // dist
	int **P = nullptr;   // path
	int findVertexIdx(const long &in) const;

	priority_queue<Edge> buildHeap();


public:
	Vertex *findVertex(const long &in) const;
	bool addVertex(const long &in);
	bool addVertex(const long &in, double x, double y);
	bool addEdge(const long &sourc, const long &dest, double w);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;
	double getRightBound() const { return rightBound; };
	double getLeftBound() const { return leftBound; };
	double getTopBound() const { return topBound; };
	double getBottomBound() const { return bottomBound; };
	

	// Fp05 - single source
	void dijkstraShortestPath(const long &s);
	void unweightedShortestPath(const long &s);
	void bellmanFordShortestPath(const long &s);
	vector<long> getPath(const long &origin, const long &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<long> getfloydWarshallPath(const long &origin, const long &dest) const;
	~Graph();

	// Fp07 - minimum spanning tree
	vector<Vertex *> calculatePrim();
	vector<Vertex *> calculateKruskal();
};

#endif /* GRAPH_H_ */
