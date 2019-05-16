#include "Vertex.h"
#include <cmath>

using namespace std;

Vertex::Vertex(long in): info(in){}

Vertex::Vertex(long in, double x, double y): info(in), x(x), y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(Vertex *d, double w) {
	adj.push_back(Edge(this, d, w));
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}

long Vertex::getInfo() const {
	return this->info;
}

double Vertex::getDist() const {
	return this->dist;
}

double Vertex::getEuclideanDist(const Vertex *  vertex2) const{
	return sqrt(pow(vertex2->x - this->x, 2) + pow(vertex2->y - this->y, 2));
}

Vertex *Vertex::getPath() const {
	return this->path;
}
