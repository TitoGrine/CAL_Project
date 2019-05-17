#include "Edge.h"

using namespace std;


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