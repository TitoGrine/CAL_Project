#include "Edge.h"

using namespace std;

Edge::Edge(Vertex *o, Vertex *d, double w): orig(o), dest(d), weight(w) {}

double Edge::getWeight() const {
	return weight;
}

bool Edge::operator<(const Edge & e2 ) const {
	return this->getWeight() > e2.getWeight();
}