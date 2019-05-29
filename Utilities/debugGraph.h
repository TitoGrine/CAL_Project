#pragma once

#include <ostream>
#include <iostream>

/**
 * @brief Prints all the vertexes info to the output separated by semicolon to allow an easier debugging
 * 
 * @tparam T Template type that has to have an overload of the << operator
 * @param verts Vector of Vertexes to be written in the ouput ostream
 * @param output Ostream where the output will be written
 */
template <class T>
void printVertex(vector<Vertex<T> *> verts, ostream & output);

/**
 * @brief Prints the vertexes info of all the destination nodes of the edges to the terminal separated by semicolon to allow an easier debugging
 * 
 * @tparam T Template type that has to have an overload of the << operator
 * @param edges Vector of edges to be shown int the terminal
 */
template <class T>
void prinntEdgesDest(vector<Edge<T>> * edges);

/**
 * @brief Prints all the vertexes info and its indexes in the main graph to the output separated by semicolon to allow an easier debugging
 * 
 * @tparam T Template type that has to have an overload of the << operator
 * @param graph Graph where the vertexes are from
 * @param verts Vector of vertexes to be written to the output ostream
 * @param output Ostream where the output will be written
 */
template <class T>
void printVertexIndex(Graph<T> * graph, vector<Vertex<T> *> verts, ostream & output);


template <class T>
void printVertex(vector<Vertex<T> *> verts, ostream & output){
	for(auto v: verts)
		output << *(v->getInfo()) << " ; ";
	output << endl;
}

template <class T>
void printVertexIndex(Graph<T> * graph, vector<Vertex<T> *> verts, ostream & output){
	for(auto v: verts)
		output << *(v->getInfo()) << " ; "  << graph->findVertexIdx(*(v->getInfo())) << endl;
	output << endl;
}

template <class T>
void prinntEdgesDest(vector<Edge<T>> * edges){
	for(unsigned int i = 0; i < edges->size(); i++)
		cout << *(edges->at(i).getDest()->getInfo()) << " ; ";
	cout << endl;
}