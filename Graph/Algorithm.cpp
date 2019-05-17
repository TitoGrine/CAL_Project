#include "Algorithm.h"


/*
vector<Vertex *> dfs(Graph * graph) {
	vector<Vertex *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	for(auto vertex: graph->getVertexSet())
		if(!vertex->getVisited())
			dfsVisit(vertex, res);
	return res;
}
*/


static void dfsVisit(Vertex *v, vector<Vertex *> & res) {
	v->setVisited(true);
	res.push_back(v);
	for(unsigned int i = 0; i < v->getAdj()->size(); i++)
		if(!v->getAdj()->at(i).getDest()->getVisited())
			dfsVisit(v->getAdj()->at(i).getDest(), res);
}

vector<Vertex *> dfs(Graph * graph, Vertex * initial) {
	vector<Vertex *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	dfsVisit(initial, res);
	return res;
}


/**
 * Analyzes an edge in single source shortest path algorithm.
 * Returns true if the target vertex was relaxed (dist, path).
 * Used by all single-source shortest path algorithms.
 */

inline bool relax(Vertex *v, Vertex *w, double weight) {
	if (v->getDist() + weight < w->getDist()) {
		w->setDist(v->getDist() + weight);
		w->setPath(v);
		return true;
	}
	else
		return false;
}

void dijkstraShortestPath(Graph * graph, const long &origin) {
	auto s = graph->initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while( ! q.empty() ) {
		auto v = q.extractMin();
		for(unsigned int i = 0; i < v->getAdj()->size(); i++) {
			auto e = v->getAdj()->at(i);
			auto oldDist = e.getDest()->getDist();
			if (relax(v, e.getDest(), e.getWeight())) {
				if (oldDist == INF)
					q.insert(e.getDest());
				else
					q.decreaseKey(e.getDest());
			}
		}
	}
}
