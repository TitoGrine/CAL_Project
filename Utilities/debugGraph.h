#pragma once

#include <ostream>
#include <iostream>

template <class T>
void printVertex(vector<Vertex<T> *> verts, ostream & output);

template <class T>
void prinntEdgesDest(vector<Edge<T>> * edges);


template <class T>
void printVertex(vector<Vertex<T> *> verts, ostream & output){
	for(auto v: verts)
		output << *(v->getInfo()) << " ; ";
	output << endl;
}

template <class T>
void prinntEdgesDest(vector<Edge<T>> * edges){
	for(unsigned int i = 0; i < edges->size(); i++)
		cout << *(edges->at(i).getDest()->getInfo()) << " ; ";
	cout << endl;
}