/*
 * Edge.h
 */
#ifndef EDGE_H_
#define EDGE_H_

//#include "Graph.h"
#include "Vertex.h"

/********************** Edge  ****************************/

template <class T> class Graph;
template <class T> class Vertex;

template <class T>
class Edge {
	Vertex<T> * orig; 	// Fp07
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight

	bool selected; // Fp07

public:
	Edge(Vertex<T> *o, Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;

	// Fp07
	double getWeight() const;

	bool operator<(const Edge<T> & e2) const;
	bool operator==(const Edge<T> & e2 ) const;


	Vertex<T> *  getOrig() const { return this->orig; };
	Vertex<T> *  getDest() const { return this->dest; };
};


template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double w): orig(o), dest(d), weight(w) {}

template <class T>
double Edge<T>::getWeight() const {
	return weight;
}

template <class T>
bool Edge<T>::operator<(const Edge<T> & e2 ) const {
	return this->getWeight() > e2.getWeight();
}

template <class T>
bool Edge<T>::operator==(const Edge<T> & e2 ) const {
	return this->getDest() == e2.getDest() && this->getOrig() == e2.getOrig();
}

#endif
