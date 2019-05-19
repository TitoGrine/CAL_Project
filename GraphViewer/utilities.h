#pragma once

#include "graphviewer.h"
#include <string>
#include "../Graph/Graph.h"

template <class T>
GraphViewer * createVertexGraphViewer(const Graph<T> * graph, int vertexSize, std::string vertexColor);

template <class T>
void addEdgesToGV(const Graph<T> * graph, GraphViewer * gv, bool bidirectional);

template <class T>
GraphViewer * createFullGraphViewer(const Graph<T> * graph, int vertexSize, std::string vertexColor);

template <class T>
void paintVertexesGV(GraphViewer * gv, int vertexSize, std::string vertexColor, const std::vector<Vertex<T> *> & vertexes);

template <class T>
GraphViewer * createVertexGraphViewer(const Graph<T> * graph, int vertexSize, string vertexColor){
	double graphWidth = graph->getRightBound() - graph->getLeftBound();
	double graphHeight = graph->getTopBound() - graph->getBottomBound();

	// Definir proporção com 800 de altura
	int gvHeight = 800;
	int gvWidth = max(gvHeight, static_cast<int>(gvHeight * graphWidth / graphHeight));
	GraphViewer *gv = new GraphViewer(gvWidth, gvHeight, false);
	gv->createWindow(gvWidth, gvHeight);

	gv->defineVertexColor(vertexColor);

	// Vertex
	for(auto i = 0; i < graph->getNumVertex(); i++){
		Vertex<T> * v = graph->getVertexSet().at(i);
		// 1º subtrair para por em 0
		// 2º regra de 3 simples
		// 3º *0.95 para reduzir um pouco tamanho (nao ir ate bordas mesmo)
		double newX = (v->getX() - graph->getLeftBound()) * gvWidth / graphWidth * 0.95;
		// Y ao contratio
		double newY = (v->getY() - graph->getBottomBound()) * gvHeight / graphHeight * 0.95;

		// 4º adicionar algo para recentrar
		newX += (0.025 * gvWidth);
		newY += (0.025 * gvHeight);
		
        gv->addNode(v->getInfo()->getID(), static_cast<int>(newX), static_cast<int>(gvHeight - newY));
		gv->setVertexSize(v->getInfo()->getID(), vertexSize);
	}

	return gv;	
}

// TODO: ver se se importam estar a desenhar 2 vezes
template <class T>
void addEdgesToGV(const Graph<T> * graph, GraphViewer * gv, bool bidirectional){
	// Edges
	int edgeID = 0;
	gv->defineEdgeCurved(false);
	for(auto i = 0; i < graph->getNumVertex(); i++){
		Vertex<T> * v = graph->getVertexSet().at(i);
		for(size_t j = 0; j < v->getAdj()->size(); j++)
			if(bidirectional)
				gv->addEdge(edgeID++, v->getInfo()->getID(), v->getAdj()->at(j).getDest()->getInfo()->getID(), EdgeType::UNDIRECTED);
			else
				gv->addEdge(edgeID++, v->getInfo()->getID(), v->getAdj()->at(j).getDest()->getInfo()->getID(), EdgeType::DIRECTED);
	}
}

template <class T>
GraphViewer * createFullGraphViewer(const Graph<T> * graph, int vertexSize, string vertexColor, bool bidirectional){
	GraphViewer * gv = createVertexGraphViewer(graph, vertexSize, vertexColor);
	addEdgesToGV(graph, gv, bidirectional);
	return gv;
}

template <class T>
void paintVertexesGV(GraphViewer * gv, int vertexSize, string vertexColor, const vector<Vertex<T> *> & vertexes){
	for(auto v : vertexes){
		gv->setVertexColor(v->getInfo()->getID(), vertexColor);
		gv->setVertexSize(v->getInfo()->getID(), vertexSize);
	}
}