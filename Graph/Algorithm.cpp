#include "Algorithm.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

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

static void printVertex(vector<Vertex *> verts, ostream & output){
	for(auto v: verts)
		output << v->getInfo() << " ; ";
	output << endl;
}

static void prinntEdgesDest(vector<Edge> * edges){
	for(unsigned int i = 0; i < edges->size(); i++)
		cout << edges->at(i).getDest()->getInfo() << " ; ";
	cout << endl;
}

struct CompareVertexPointer
{
    long vertexInfo;

    CompareVertexPointer(long info) : vertexInfo(info) {}

    bool operator()(const Vertex * vertex) const
    {
        return (vertex->getInfo() == vertexInfo);
    }
};

vector<Vertex *> scc(Graph * graph, Vertex * initial){
	ofstream out;
	out.open("teste.txt");
	vector<Vertex *> res_normal = dfs(graph, initial);
	printVertex(res_normal, out);
	// TODO: mudar para não alterar proprio grafo
	Graph invertedGraph = graph->invert();

	// TODO: optimize em vez de reaproveitar funcao
	Vertex * invInitial = invertedGraph.findVertex(initial->getInfo());

	vector<Vertex *> res_invert = dfs(&invertedGraph, invInitial);

	printVertex(res_invert, out);
	
	vector<Vertex *> res;
	for(auto v: res_normal)
		if(find_if(res_invert.begin(), res_invert.end(), CompareVertexPointer(v->getInfo())) != res_invert.end())
			res.push_back(v);

	printVertex(res, out);
	out.close();
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
