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

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()


/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	double rightBound, leftBound, topBound, bottomBound;	

	// Fp05
	Vertex<T> * initSingleSource(const T &orig);
	double ** W = nullptr;   // dist
	int **P = nullptr;   // path
	int findVertexIdx(const T &in) const;

	priority_queue<Edge<T>> buildHeap();


public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in, double x, double y);
	bool addEdge(const T &sourc, const T &dest, double w);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
	~Graph();

	// Fp07 - minimum spanning tree
	vector<Vertex<T>*> calculatePrim();
	vector<Vertex<T>*> calculateKruskal();

	double getRightBound() const { return this->rightBound; };
	double getLeftBound() const { return this->leftBound; };
	double getTopBound() const { return this->topBound; };
	double getBottomBound() const { return this->bottomBound; };

	Vertex<T> *findInitial() const;
	Vertex<T> *findFinal() const;
	Graph<T> invert();
	

};


#endif /* GRAPH_H_ */
