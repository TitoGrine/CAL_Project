#include <iostream>
#include <thread>

#include "Graph/Algorithm.h"

#include "Utilities/parser.h"
#include "Utilities/MapInfo.h"
#include "Utilities/debugGraph.h"
#include "Graph/Graph.h"
#include "Interface/Input.h"
#include "Interface/ConsoleFunctions.h"
#include "GraphViewer/utilities.h"

using namespace std;

#define UNDIRECTED true

Application mainApp;

void InicialMenu();
void MapOperationsMenu();
void ProblemsMenu();
void Prob2Menu();

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
	GraphViewer * gv = createFullGraphViewer(graph, 10, "YELLOW", UNDIRECTED);
	gv->rearrange();
	getchar();
	gv->closeWindow();
}

//-----------------------------------------------------------------------------------------------------------------------//

void showPointTerminal(Graph<MapInfo> * graph, bool initial){
	MapInfo * mi;
	Vertex<MapInfo> * v;
	if(initial){
		if((mi = mainApp.getInitial()) == NULL){
			cout << "\n There is no initial point to be shown\n\n";
			return;
		}
		v = graph->findVertex(*mi);
		cout << "\n Info:\t" << mi->getID() << "\n X:\t" << v->getX() << "\n Y:\t" << v->getY() << endl;
		return;
	}
	if((mi = mainApp.getLast()) == NULL){
		cout << "\n There is no final point to be shown\n\n";
		return;
	}
	v = graph->findVertex(*mi);
	cout << "\n Info:\t" << mi->getID() << "\n X:\t" << v->getX() << "\n Y:\t" << v->getY() << endl;
}

//-----------------------------------------------------------------------------------------------------------------------//

void showPointGV(Graph<MapInfo> * graph, bool initial){
	MapInfo * mi;
	if(initial){
		if((mi = mainApp.getInitial()) == NULL){
			cout << "\n There is no initial point to be shown\n\n";
			return;
		}
		cout << " Map shown in the GraphViewer" << endl;
		GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
		gv->setVertexSize(mi->getID(), 20);
		gv->setVertexColor(mi->getID(), "GREEN");
		gv->setVertexLabel(mi->getID(), "Start");
		gv->rearrange();
		getchar();
		gv->closeWindow();
		return;
	}
	if((mi = mainApp.getLast()) == NULL){
		cout << "\n There is no final point to be shown\n\n";
		return;
	}
	cout << " Map shown in the GraphViewer" << endl;
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	gv->setVertexSize(mi->getID(), 20);
	gv->setVertexColor(mi->getID(), "RED");
	gv->setVertexLabel(mi->getID(), "End");
	gv->rearrange();
	getchar();
	gv->closeWindow();
}

//-----------------------------------------------------------------------------------------------------------------------//

// TODO: escolher nome melhor
void showPathGV(Graph<MapInfo> * graph, Vertex<MapInfo> * initial, vector<Vertex<MapInfo> *> * points){
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", *points);
	gv->setVertexSize(initial->getInfo()->getID(), 20);
	gv->setVertexColor(initial->getInfo()->getID(), "GREEN");
	gv->setVertexLabel(initial->getInfo()->getID(), "Start");
	gv->rearrange();
	getchar();
	gv->closeWindow();

}

void showPathGV(Graph<MapInfo> * graph, Vertex<MapInfo> * initial, Vertex<MapInfo> * final, vector<Vertex<MapInfo> *> * points){
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", *points);
	gv->setVertexSize(initial->getInfo()->getID(), 20);
	gv->setVertexColor(initial->getInfo()->getID(), "GREEN");
	gv->setVertexLabel(initial->getInfo()->getID(), "Start");

	gv->setVertexSize(final->getInfo()->getID(), 20);
	gv->setVertexColor(final->getInfo()->getID(), "RED");
	gv->setVertexLabel(final->getInfo()->getID(), "End");
	
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

void addPoint(bool initial){
	string question = initial? " Initial Vertex ID (0 - " :  " Final Vertex ID (0 - ";
	question += to_string(mainApp.getMainGraph()->getNumVertex());
	question +=  ") ? ";
	if(initial){
		if(mainApp.getInitial() != NULL)
			cout << "\n There is already a starting point\n\n";
		else{
			int initialID =  menuInput(question, 0, mainApp.getMainGraph()->getNumVertex() - 1);
			if(!mainApp.addInitial(*(mainApp.getMainGraph()->getVertexSet().at(initialID)->getInfo())))
				cout << "\n Error adding initial point\n\n";
		}
		return;
	}
	if(mainApp.getLast() != NULL)
		cout << "\n There is already a final point\n\n";
	else{
		int finalID =  menuInput(question, 0, mainApp.getMainGraph()->getNumVertex() - 1);
		if(!mainApp.addLast(*(mainApp.getMainGraph()->getVertexSet().at(finalID)->getInfo())))
			cout << "\n Error adding final point\n\n";
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

void removePoint(bool initial){
	if(initial){
		if(!mainApp.removeInitial())
			cout << "\n Error removing initial point\n\n";
		return;
	}
	if(!mainApp.removeLast())
		cout << "\n Error removing final point\n\n";

}

//=======================================================================================================================//

/**
*  +------------------------+
*  |                        |
*  |          MENUS         |
*  |                        |
*  +------------------------+
*/

bool DeliveryPlaceMenu() {
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

	mainApp.addDelivery(mainApp.getRandomShopByType((map_info_t)option_number));
	return true;
}

void Prob1Menu() {
	
	DeliveryPlaceMenu();

	header("ONE TRUCK - ONE DELIVERY");

	int option_number;

	std::cout << " CHOOSE AN ALGORITHM:" << endl << endl;

	std::cout << "   1 - Dijkstra Algorithm" << endl;
	std::cout << "   2 - A* Algorithm" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

	MapInfo delivery = mainApp.getDeliveries().at(0);
	vector<MapInfo> solutionPath;
	switch (option_number) {
		case 1 :
			solutionPath = bidirectionalDijkstra(mainApp.getSmallGraph(), *(mainApp.getInitial()), delivery, *(mainApp.getLast()), UNDIRECTED);
			//TODO: Show solution to user
			break;
		case 2 :
			solutionPath = bidirectionalAStar(mainApp.getSmallGraph(), *(mainApp.getInitial()), delivery, *(mainApp.getLast()), UNDIRECTED);
			//TODO: Show solution to user
			break;
		case 3 :
			ProblemsMenu();
			return;
		default:
			break;
	}

	
}

void NearestNeighbourMenu(Graph<MapInfo> * graph, vector<Vertex<MapInfo> *>* solutionPath){
	header("ONE TRUCK - MULTIPLE DELIVERIES");

		int option_number;

		std::cout << " CHOOSE A DISTANCE CALCULATING ALGORITHM:" << endl << endl;

		std::cout << "   1 - Using Euclidean Distance" << endl;
		std::cout << "   2 - Using Floyd-Warshall's Algorithm" << endl;
		std::cout << "   0 - Go Back" << endl << endl;

		option_number = menuInput(" Option ? ", 0, 2);

		switch (option_number) {
		case 1 :
			*solutionPath = NearestNeighborEuclidean(graph, *mainApp.getInitial(), mainApp.getDeliveries(), *mainApp.getLast());
			system("pause");		
			showPathGV(graph, graph->findVertex(*mainApp.getInitial()), graph->findVertex(*mainApp.getLast()), solutionPath);
			break;
		case 2 :
			*solutionPath = NearestNeighborFloyd(graph, *mainApp.getInitial(), mainApp.getDeliveries(), *mainApp.getLast());
			system("pause");
			showPathGV(graph, graph->findVertex(*mainApp.getInitial()), graph->findVertex(*mainApp.getLast()), solutionPath);
			//TODO: Show solution to user
			break;
		case 0 :
			system("cls");
			Prob2Menu();
			return;
		default:
			break;
	}
}

void Prob2Menu() {

	while (DeliveryPlaceMenu());

	header("ONE TRUCK - MULTIPLE DELIVERIES");

	int option_number;

	std::cout << " CHOOSE AN ALGORITHM:" << endl << endl;

	std::cout << "   1 - Nearest Neighbor Algorithm" << endl;
	std::cout << "   2 - Local Search (2-opt) Algorithm" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);

	std::vector<Vertex<MapInfo> *> solutionPath;

	switch (option_number) {
		case 1 :
			NearestNeighbourMenu(mainApp.getSmallGraph(), &solutionPath);
			//TODO: Show solution to user
			break;
		case 2 :
			//TODO: Call 2-opt function
			//TODO: Show solution to user
			break;
		case 0 :
			system("cls");
			ProblemsMenu();
			return;
		default:
			break;
	}
}

void ProblemsMenu() {
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
			Prob1Menu();
			break;
		case 2:
			Prob2Menu();
			break;
		case 3:

			break;
		case 0:
			system("cls");
			MapOperationsMenu();
			break;
		default: 
			break;
	}
}

// TODO: ver melhor como vai ser a seleção de um ponto

void PointMenu(bool initial){
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
		addPoint(initial);
		PointMenu(initial);
		break;
	case 2:
		removePoint(initial);
		PointMenu(initial);
		break;
	case 3:
		showPointTerminal(mainApp.getMainGraph(), initial);
		system("pause");
		PointMenu(initial);
		break;
	case 4:
		showPointGV(mainApp.getMainGraph(), initial);
		PointMenu(initial);
		break;
	case 0:
		system("cls");
		MapOperationsMenu();
		return;
  default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void ConnectionMenu(){
	header("TEST CONNECTIVITY");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Show SCC in Terminal" << endl;
	std::cout << "   2 - Show SCC in GraphViewer" << endl;
	std::cout << "   3 - Test Initial - Final Connection" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 3);
	
	Vertex<MapInfo> * initial;
	MapInfo * lastMI = mainApp.getLast();
	vector<Vertex<MapInfo> *> res;

	if(option_number != 0){
		// TODO: fazer aquela animacao dos 3 pontos
		cout << " Calculating..." << endl;

		initial = mainApp.getMainGraph()->findVertex(*(mainApp.getInitial()));
		res = scc(mainApp.getMainGraph(), initial, UNDIRECTED);
	}

	switch (option_number)
	{
	case 1:
		printVertex(res, cout);
		system("pause");
		ConnectionMenu();
		break;
	case 2:
		showPathGV(mainApp.getMainGraph(), initial, &res);
		ConnectionMenu();
		break;
	case 3:
		if(lastMI == NULL)
			cout << " Final Vertex not define\n\n";
		else if(containsVertex(res, mainApp.getMainGraph()->findVertex(*lastMI)))
			cout << " The Initial and Final Points are connected\n\n";
		else
			cout << " There is no connection between the Initial and the Final Point\n\n";
		break;
	case 0:
		system("cls");
		MapOperationsMenu();
		return;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void MapOperationsMenu(){
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
		PointMenu(true);
		break;
	case 2:
		PointMenu(false);
		break;
	case 3:
		if(mainApp.getInitial() == NULL){
			cout << "\n You must first enter a intial point\n\n";
			MapOperationsMenu();
		}
		else
			ConnectionMenu();
		break;
	case 4:
		header("SOLVE PROBLEMS");
		ProblemsMenu();
		break;
	case 0:
		system("cls");
		InicialMenu();
		return;
    default:break;
    }

}

//-----------------------------------------------------------------------------------------------------------------------//

void MapMenu()
{
	int option_number;
	Graph<MapInfo> * graph = new Graph<MapInfo>();


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
		*graph = buildGraph("Aveiro", UNDIRECTED);
		buildApplication(&mainApp, "Aveiro", graph);
		break;
	case 2:
		*graph = buildGraph("Braga", UNDIRECTED);
		buildApplication(&mainApp, "Braga", graph);		
		break;
	case 3:
		*graph = buildGraph("Coimbra", UNDIRECTED);
		buildApplication(&mainApp, "Coimbra", graph);		
		break;
	case 4:
		*graph = buildGraph("Ermesinde", UNDIRECTED);
		buildApplication(&mainApp, "Ermesinde", graph);		
		break;
	case 5:
		*graph = buildGraph("Fafe", UNDIRECTED);
		buildApplication(&mainApp, "Fafe", graph);
		break;
	case 6:
		*graph = buildGraph("Gondomar", UNDIRECTED);	
		buildApplication(&mainApp, "Gondomar", graph);		
		break;
	case 7:
		*graph = buildGraph("Lisboa", UNDIRECTED);
		buildApplication(&mainApp, "Lisboa", graph);		
		break;
	case 8:
		*graph = buildGraph("Maia", UNDIRECTED);
		buildApplication(&mainApp, "Maia", graph);		
		break;
	case 9:
		*graph = buildGraph("Porto", UNDIRECTED);
		buildApplication(&mainApp, "Porto", graph);		
		break;
	case 10:
		*graph = buildGraph("Portugal", UNDIRECTED);
		buildApplication(&mainApp, "Portugal", graph);		
		break;
	case 11:
		*graph = buildGraph("Viseu", UNDIRECTED);
		buildApplication(&mainApp, "Viseu", graph);		
		break;
	case 0:
		break;
    default:break;
    }
	system("cls");
	InicialMenu();

}

//-----------------------------------------------------------------------------------------------------------------------//

void InicialMenu()
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
		MapMenu();
		break;
	case 2:
		if(mainApp.getMainGraph() == NULL)
			cout << "\n You must first choose a map\n\n";
		else{
			header("MAP");
			showGraph(mainApp.getMainGraph());
			system("cls");
		}
		InicialMenu();
		break;
	case 3:
		if(mainApp.getMainGraph() == NULL){
			cout << "\n You must first choose a map\n\n";
			InicialMenu();
		}
		else
			MapOperationsMenu();
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

	InicialMenu();

	return 0;
}
