#include <iostream>
#include <thread>

#include "Graph/Algorithm.h"

#include "Utilities/parser.h"
#include "Utilities/MapInfo.h"
#include "Graph/Graph.h"
#include "Interface/Input.h"
#include "Interface/ConsoleFunctions.h"
#include "GraphViewer/utilities.h"

using namespace std;

void InicialMenu(Graph<MapInfo> * graph);
void MapOperationsMenu(Graph<MapInfo> * graph);
void ProblemsMenu(Graph<MapInfo> * graph);

/**
*  +------------------------+
*  |                        |
*  |        HEADERs         |
*  |                        |
*  +------------------------+
*/

/**
* Writes a neat header in the console with the title centerd and a line above and below all across the screen
*
* @param	title		Title of the Header
*
* @see		centerWord			(@ConsoleFunctions)
* @see		lineAcrossConsole	(@ConsoleFunctions)
*/
void mainHeader(string title)
{
	setcolor(3);
	lineAcrossConsole('=');
	cout << endl;
	setcolor(14);
	centerWord(title);
	cout << endl;
	setcolor(3);
	lineAcrossConsole('=');
	cout << endl;
	setcolor(15);
}

//-----------------------------------------------------------------------------------------------------------------------//

/**
* Writes a neat subHeader in the console with the title and a line of '-' above and below all across the screen
*
* @param	header		Title of the subHeader
*
* @see		lineAcrossConsole	(@ConsoleFunctions)
*/
void header(const string &header)
{
	cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	setcolor(14);
	cout << " " << header;
	cout << endl;
	setcolor(3);
	lineAcrossConsole('-');
	cout << endl;
	setcolor(15);
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |        DISPLAY         |
*  |                        |
*  +------------------------+
*/

void showGraph(Graph<MapInfo> * graph){
	cout << " Map shown in the GraphViewer" << endl;
	GraphViewer * gv = createFullGraphViewer(graph, 10, "YELLOW");
	gv->rearrange();
	getchar();
	gv->closeWindow();
}

//-----------------------------------------------------------------------------------------------------------------------//

void showPointTerminal(Graph<MapInfo> * graph, bool initial){
	Vertex<MapInfo> * v;
	if(initial){
		if((v = graph->findInitial()) == NULL){
			cout << "\n There is no initial point to be shown\n\n";
			return;
		}
		cout << "\n Info:\t" << v->getInfo()->getID() << "\n X:\t" << v->getX() << "\n Y:\t" << v->getY() << endl;
		return;
	}
	if((v = graph->findFinal()) == NULL){
		cout << "\n There is no final point to be shown\n\n";
		return;
	}
	cout << "\n Info:\t" << v->getInfo()->getID() << "\n X:\t" << v->getX() << "\n Y:\t" << v->getY() << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void showPointGV(Graph<MapInfo> * graph, bool initial){
	Vertex<MapInfo> * v;
	if(initial){
		if((v = graph->findInitial()) == NULL){
			cout << "\n There is no initial point to be shown\n\n";
			return;
		}
		cout << " Map shown in the GraphViewer" << endl;
		GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
		gv->setVertexSize(v->getInfo()->getID(), 20);
		gv->setVertexColor(v->getInfo()->getID(), "GREEN");
		gv->setVertexLabel(v->getInfo()->getID(), "Start");
		gv->rearrange();
		getchar();
		gv->closeWindow();
		return;
	}
	if((v = graph->findFinal()) == NULL){
		cout << "\n There is no final point to be shown\n\n";
		return;
	}
	cout << " Map shown in the GraphViewer" << endl;
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	gv->setVertexSize(v->getInfo()->getID(), 20);
	gv->setVertexColor(v->getInfo()->getID(), "RED");
	gv->setVertexLabel(v->getInfo()->getID(), "End");
	gv->rearrange();
	getchar();
	gv->closeWindow();
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |          ADD           |
*  |                        |
*  +------------------------+
*/

void addPoint(Graph<MapInfo> * graph, bool initial){
	string question = initial? " Initial Vertex ID (0 - " :  " Final Vertex ID (0 - ";
	question += to_string(graph->getNumVertex());
	question +=  ") ? ";
	if(initial){
		if(graph->findInitial() != NULL)
			cout << "\n There is already a starting point\n\n";
		else{
			
			int initialID =  menuInput(question, 0, graph->getNumVertex() - 1);
			graph->getVertexSet().at(initialID)->getInfo()->setInitial();
		}
		return;
	}
	if(graph->findFinal() != NULL)
		cout << "\n There is already a final point\n\n";
	else{
		int finalID =  menuInput(question, 0, graph->getNumVertex() - 1);
		graph->getVertexSet().at(finalID)->getInfo()->setFinal();
	}
}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |         REMOVE         |
*  |                        |
*  +------------------------+
*/

void removePoint(Graph<MapInfo> * graph, bool initial){
	Vertex<MapInfo> *v;
	if(initial){
		if((v = graph->findInitial()) != NULL)
			v->getInfo()->removeInitial();
		else
			cout << "\n There is no initial point to be removed\n\n";
		return;
	}
	if((v = graph->findFinal()) != NULL)
		v->getInfo()->removeFinal();
	else
		cout << "\n There is no final point to be removed\n\n";

}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |          MENUS         |
*  |                        |
*  +------------------------+
*/

bool DeliveryPlaceMenu(Graph<MapInfo> * graph) {
	header("DELIVERY PLACE");

	int option_number;

	std::cout << " CHOOSE A DELIVERY PLACE:" << endl << endl;

	std::cout << "   1 - Department Store" << endl;
	std::cout << "   2 - Variety Store" << endl;
	std::cout << "   3 - SuperMarket" << endl;
	std::cout << "   4 - DoItYourself" << endl;
	std::cout << "   5 - Convenience" << endl;
	std::cout << "   6 - Clothes" << endl;
	std::cout << "   7 - Hardware" << endl;
	std::cout << "   8 - Furniture" << endl;
	std::cout << "   9 - Eletronics" << endl;
	std::cout << "   10 - Mobile Phone" << endl;
	std::cout << "   11 - Shoes" << endl;
	std::cout << "   12 - Alcohol" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 12);

	if(option_number == 0) return false;

	return graph->addDelivery(graph->getShop(option_number));
}

void oneTruckOneDelProb(Graph<MapInfo> * graph) {
	
	while (DeliveryPlaceMenu(graph));

	header("ONE TRUCK - ONE DELIVERY");

	int option_number;

	std::cout << " CHOOSE AN ALGORITHM:" << endl << endl;

	std::cout << "   1 - Dijkstra Algorithm" << endl;
	std::cout << "   2 - A* Algorithm" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

	MapInfo delivery = graph->getDeliveries().at(0);
	vector<MapInfo> solutionPath;
	switch (option_number) {
		case 1 :
			solutionPath = bidirectionalDijkstra(graph, *(graph->findInitial()->getInfo()), delivery, *(graph->findFinal()->getInfo()));
			//TODO: Show solution to user
			break;
		case 2 :
			solutionPath = bidirectionalAStar(graph, *(graph->findInitial()->getInfo()), delivery, *(graph->findFinal()->getInfo()));
			//TODO: Show solution to user
			break;
		case 3 :
			ProblemsMenu(graph);
			return;
		default:
			break;
	}

	
}

void ProblemsMenu(Graph<MapInfo> * graph) {
	header("PROBLEMS");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - One Truck - One Delivery" << endl;
	std::cout << "   2 - One Truck - Multiple Deliveries" << endl;
	std::cout << "   3 - Mutiple Trucks - Multiple Deliveries" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
		case 1: 
			oneTruckOneDelProb(graph);
			break;
		case 2:

			break;
		case 3:

			break;
		case 0:
			MapOperationsMenu(graph);
			break;
		default: 
			break;
	}
}

// TODO: ver melhor como vai ser a seleção de um ponto

void PointMenu(Graph<MapInfo> * graph, bool initial){
	if(initial)	header("INITIAL POINT");
	else header("FINAL POINT");


	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Add Point" << endl;
	std::cout << "   2 - Remove Point" << endl;
	std::cout << "   3 - Show Point Terminal" << endl;
	std::cout << "   4 - Show Point GraphViewer" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		addPoint(graph, initial);
		PointMenu(graph, initial);
		break;
	case 2:
		removePoint(graph, initial);
		PointMenu(graph, initial);
		break;
	case 3:
		showPointTerminal(graph, initial);
		PointMenu(graph, initial);
		break;
	case 4:
		showPointGV(graph, initial);
		PointMenu(graph, initial);
		break;
	case 0:
		system("cls");
		MapOperationsMenu(graph);
		return;
  default:break;
    }
}

void ConnectionMenu(Graph<MapInfo> * graph){
	header("TEST CONNECTIVITY");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Show SCC in Terminal" << endl;
	std::cout << "   2 - Show SCC in GraphViewer" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

	// TODO: fazer aquela animacao dos 3 pontos
	cout << " Calculating..." << endl;

	Vertex<MapInfo> * initial = graph->findInitial();
	vector<Vertex<MapInfo> *> res = dfs(graph, initial);

	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", res);
	gv->setVertexSize(initial->getInfo()->getID(), 20);
	gv->setVertexColor(initial->getInfo()->getID(), "GREEN");
	gv->setVertexLabel(initial->getInfo()->getID(), "Start");
	gv->rearrange();
	getchar();
	gv->closeWindow();

	switch (option_number)
	{
	case 1:
		addPoint(graph, initial);
		ConnectionMenu(graph);
		break;
	case 2:
		removePoint(graph, initial);
		ConnectionMenu(graph);
		break;
	case 0:
		system("cls");
		MapOperationsMenu(graph);
		return;
    default:break;
    }
}

void MapOperationsMenu(Graph<MapInfo> * graph){
	header("MAP OPERATIONS");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Initial Point" << endl;
	std::cout << "   2 - Final Point" << endl;
	std::cout << "   3 - Test Conectivity" << endl;
	std::cout << "   4 - Solve Problems" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
	case 1:
		PointMenu(graph, true);
		break;
	case 2:
		PointMenu(graph, false);
		break;
	case 3:
		if(graph->findInitial() == NULL){
			cout << "\n You must first enter a intial point\n\n";
			MapOperationsMenu(graph);
		}
		else{
			ConnectionMenu(graph);
		}
		break;
	case 4:
		header("SOLVE PROBLEMS");
		ProblemsMenu(graph);
		break;
	case 0:
		system("cls");
		InicialMenu(graph);
		return;
    default:break;
    }

}

void MapMenu(Graph<MapInfo> * graph)
{
	int option_number;

	std::cout << " Which Map do you want:" << endl << endl;
	std::cout << "   1 - Aveiro" << endl;
	std::cout << "   2 - Braga" << endl;
	std::cout << "   3 - Coimbra" << endl;
	std::cout << "   4 - Ermesinde" << endl;
	std::cout << "   5 - Fafe" << endl;
	std::cout << "   6 - Gondomar" << endl;
	std::cout << "   7 - Lisboa" << endl;
	std::cout << "   8 - Maia" << endl;
	std::cout << "   9 - Porto" << endl;
	std::cout << "   10 - Portugal" << endl;
	std::cout << "   11 - Viseu" << endl;
	std::cout << "   0 - Go back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 11);
	switch (option_number)
	{
	case 1:
		*graph = buildGraph("Aveiro");
		break;
	case 2:
		*graph = buildGraph("Braga");		
		break;
	case 3:
		*graph = buildGraph("Coimbra");		
		break;
	case 4:
		*graph = buildGraph("Ermesinde");
		break;
	case 5:
		*graph = buildGraph("Fafe");		
		break;
	case 6:
		*graph = buildGraph("Gondomar");		
		break;
	case 7:
		*graph = buildGraph("Lisboa");		
		break;
	case 8:
		*graph = buildGraph("Maia");		
		break;
	case 9:
		*graph = buildGraph("Porto");		
		break;
	case 10:
		*graph = buildGraph("Portugal");		
		break;
	case 11:
		*graph = buildGraph("Viseu");		
		break;
	case 0:
		break;
    default:break;
    }
	system("cls");
	InicialMenu(graph);

}

//-----------------------------------------------------------------------------------------------------------------------//

void InicialMenu(Graph<MapInfo> * graph)
{
	mainHeader("Welcome to the Smart Delivery");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Choose Map" << endl;
	std::cout << "   2 - Show Map" << endl;
	std::cout << "   3 - Map Operations" << endl;
	std::cout << "   0 - Exit" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);

	switch (option_number)
	{
	case 1:
		header("CHOOSE MAP");
		MapMenu(graph);
		break;
	case 2:
		if(graph == NULL)
			cout << "\n You must first choose a map\n\n";
		else{
			header("MAP");
			showGraph(graph);
			system("cls");
		}
		InicialMenu(graph);
		break;
	case 3:
		if(graph == NULL){
			cout << "\n You must first choose a map\n\n";
			InicialMenu(graph);
		}
		else
			MapOperationsMenu(graph);
		break;
	case 0:
		system("cls");
		return;
    default:break;
    }
}


//=======================================================================================================================//

int main() {	
	system("title   SMART DELIVERY");

	Graph<MapInfo> graph;

	InicialMenu(&graph);

	return 0;
}

