/*
 * Vertex.h
 */
#ifndef VERTEX_H_
#define VERTEX_H_
/************************* Vertex  **************************/

#include <vector>
#include "Edge.h"
#include "../Utilities/MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;

	double _x, _y;

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in, double x, double y);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex<T> *getPath() const;

	double getX() const { return this->_x; };
	double getY() const { return this->_y; };

	double getEuclideanDist(const Vertex<T> *  vertex2) const;


	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


#endif
