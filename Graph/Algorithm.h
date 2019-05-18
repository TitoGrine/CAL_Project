#pragma once

#include "Graph.h"
#include "../Utilities/debugGraph.h"
#include <iostream>
#include <ostream>
#include <fstream>

template <class T>
std::vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial);

template <class T>
std::vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial);

template <class T>
void dijkstraShortestPath(Graph<T> * graph, const T &s);

template <class T>
void dfsVisit(Vertex<T> *v, vector<Vertex<T> *> & res) {
	v->setVisited(true);
	res.push_back(v);
	for(unsigned int i = 0; i < v->getAdj()->size(); i++)
		if(!v->getAdj()->at(i).getDest()->getVisited())
			dfsVisit(v->getAdj()->at(i).getDest(), res);
}

template <class T>
vector<Vertex<T> *> dfs(Graph<T> * graph, Vertex<T> * initial) {
	vector<Vertex<T> *> res;
	for(auto vertex: graph->getVertexSet())
		vertex->setVisited(false);
	dfsVisit(initial, res);
	return res;
}

template <class T>
bool containsVertex(vector<Vertex<T> *> vectorVert, Vertex<T> * vert){
	for(auto v : vectorVert)
		if(vert->getInfo() == v->getInfo())
			return true;
	return false;
}


template <class T>
vector<Vertex<T> *> scc(Graph<T> * graph, Vertex<T> * initial){
	ofstream out;
	out.open("teste.txt");
	vector<Vertex<T> *> res_normal = dfs(graph, initial);
	printVertex(res_normal, out);
	// TODO: mudar para não alterar proprio grafo
	Graph<T> invertedGraph = graph->invert();

	// TODO: optimize em vez de reaproveitar funcao
	Vertex<T> * invInitial = invertedGraph.findVertex(initial->getInfo());

	vector<Vertex<T> *> res_invert = dfs(&invertedGraph, invInitial);

	printVertex(res_invert, out);
	
	vector<Vertex<T> *> res;
	for(auto v: res_normal)
		if(containsVertex(res, v))
			res.push_back(v);

	printVertex(res, out);
	out.close();
	return res;
}
