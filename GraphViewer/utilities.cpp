#include "utilities.h"
#include <cmath>

using namespace std;

GraphViewer * createGraphViewer(const Graph * graph){
	double graphWidth = graph->getRightBound() - graph->getLeftBound();
	double graphHeight = graph->getTopBound() - graph->getBottomBound();

	// Definir proporção com 1000 de altura
	int gvHeight = 1000;
	int gvWidth = max(gvHeight, static_cast<int>(gvHeight * graphWidth / graphHeight));
	GraphViewer *gv = new GraphViewer(gvWidth, gvHeight, false);
	gv->createWindow(gvWidth, gvHeight);

	// Vertex
	for(auto i = 0; i < graph->getNumVertex(); i++){
		Vertex * v = graph->getVertexSet().at(i);
		// 1º subtrair para por em 0
		// 2º regra de 3 simples
		// 3º *0.95 para reduzir um pouco tamanho (nao ir ate bordas mesmo)
		double newX = (v->getX() - graph->getLeftBound()) * gvWidth / graphWidth * 0.95;
		// Y ao contratio
		double newY = (v->getY() - graph->getBottomBound()) * gvHeight / graphHeight * 0.95;

		// 4º adicionar algo para recentrar
		newX += (0.025 * gvWidth);
		newY += (0.025 * gvHeight);
		
        gv->addNode(v->getInfo(), static_cast<int>(newX), static_cast<int>(gvHeight - newY));
	}

	// Edges
	int edgeID = 0;
	for(auto i = 0; i < graph->getNumVertex(); i++){
		Vertex * v = graph->getVertexSet().at(i);
		for(size_t j = 0; j < v->getAdj()->size(); j++)
			gv->addEdge(edgeID++, v->getInfo(), v->getAdj()->at(j).getDest()->getInfo(), EdgeType::DIRECTED);

	}

	return gv;	
}