#include "Vertex.h"

using namespace std;

template <class T>
Vertex<T>::Vertex(T in, double x, double y): info(in), _x(x), _y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
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
	return sqrt(pow(vertex2->_x - this->_x, 2) + pow(vertex2->_y - this->_y, 2));
}