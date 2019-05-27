/*
 * Vertex.h
 */
#ifndef VERTEX_H_
#define VERTEX_H_
/************************* Vertex  **************************/

#include <vector>
#include <cmath>
//#include "Edge.h"
#include "../Utilities/MutablePriorityQueue.h"

template <class T> class Edge;
template <class T> class Vertex;
template <class T> class Graph;

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	double dist = 0;
	Vertex<T> *path = nullptr;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;

	double vertexX, vertexY;

	void addEdge(Vertex<T> *dest, double w);

public:
	Vertex(T in, double x, double y);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T * getInfo();
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge<T>> * getAdj() { return &adj; };

	void setDist(double dist) { this->dist = dist; };
	void setPath(Vertex * v) { this->path = v; };
	void setVisited(bool visited) { this->visited = visited; };
	bool getVisited() const { return this->visited; };

	double getX() const { return this->vertexX; };
	double getY() const { return this->vertexY; };

	double getEuclideanDist(const Vertex<T> *  vertex2) const;
	double getManhattanDist(const Vertex<T> * vertex2) const;

	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};

template <class T>
Vertex<T>::Vertex(T in, double x, double y): info(in), vertexX(x), vertexY(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(this, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T * Vertex<T>::getInfo() {
	return &(this->info);
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
double Vertex<T>::getEuclideanDist(const Vertex<T> *  vertex2) const{
	return sqrt(pow(vertex2->vertexX - this->vertexY, 2) + pow(vertex2->vertexX - this->vertexY, 2));
}

template <class T>
double Vertex<T>::getManhattanDist(const Vertex<T> * vertex2) const{
	return abs(this->vertexX - vertex2->vertexX) + abs(this->vertexY - vertex2->vertexY);
}



#endif
