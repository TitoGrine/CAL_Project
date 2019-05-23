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

#define UNDIRECTED_GRAPH true

Application mainApp;
//Graph<MapInfo> graph;


void InicialMenu();
void MapOperationsMenu();
void ProblemsMenu();
void Prob1Menu();
void Prob2Menu();
void Prob3Menu();

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
	GraphViewer * gv = createFullGraphViewer(graph, 10, "YELLOW", UNDIRECTED_GRAPH);
	gv->rearrange();
	getchar();
	gv->closeWindow();
}

//-----------------------------------------------------------------------------------------------------------------------//

void showGraph(Graph<MapInfo> * graph, MapInfo * initial, MapInfo * final){
	cout << " Map shown in the GraphViewer" << endl;
	GraphViewer * gv = createFullGraphViewer(graph, 10, "YELLOW", UNDIRECTED_GRAPH);
	
	gv->setVertexSize(initial->getID(), 20);
	gv->setVertexColor(initial->getID(), "GREEN");
	gv->setVertexLabel(initial->getID(), "Start");

	gv->setVertexSize(final->getID(), 20);
	gv->setVertexColor(final->getID(), "RED");
	gv->setVertexLabel(final->getID(), "End");
	
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
void showPathGV(Graph<MapInfo> * graph, MapInfo * initial, vector<Vertex<MapInfo> *> * points){
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", *points);
	gv->setVertexSize(initial->getID(), 20);
	gv->setVertexColor(initial->getID(), "GREEN");
	gv->setVertexLabel(initial->getID(), "Start");
	gv->rearrange();
	getchar();
	gv->closeWindow();

}

void showPathGV(Graph<MapInfo> * graph, MapInfo * initial, MapInfo * final, vector<Vertex<MapInfo> *> * points){
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", *points);
	gv->setVertexSize(initial->getID(), 20);
	gv->setVertexColor(initial->getID(), "GREEN");
	gv->setVertexLabel(initial->getID(), "Start");

	gv->setVertexSize(final->getID(), 20);
	gv->setVertexColor(final->getID(), "RED");
	gv->setVertexLabel(final->getID(), "End");
	
	gv->rearrange();
	getchar();
	gv->closeWindow();

}

void paintMapInfoVertexes(GraphViewer * gv, int vertexSize, string vertexColor, const vector<MapInfo> & points){
	for(auto mi :  points){
		gv->setVertexColor(mi.getID(), vertexColor);
		gv->setVertexSize(mi.getID(), vertexSize);
	}
}

void showPathGV(Graph<MapInfo> * graph, MapInfo * initial, MapInfo * final, const vector<MapInfo> & deliveries, vector<Vertex<MapInfo> *> * points){
	GraphViewer * gv = createVertexGraphViewer(graph, 4, "GRAY");
	paintVertexesGV(gv, 10, "YELLOW", *points);
	paintMapInfoVertexes(gv, 15, "BLUE", deliveries);
	gv->setVertexSize(initial->getID(), 20);
	gv->setVertexColor(initial->getID(), "GREEN");
	gv->setVertexLabel(initial->getID(), "Start");

	gv->setVertexSize(final->getID(), 20);
	gv->setVertexColor(final->getID(), "RED");
	gv->setVertexLabel(final->getID(), "End");

	int edgeID = 0;
	gv->defineEdgeCurved(false);
	for(auto i = 0; i < graph->getNumVertex(); i++){
		Vertex<MapInfo> * v = graph->getVertexSet().at(i);
		if(containsVertex(*points, v)){
			for(size_t j = 0; j < v->getAdj()->size(); j++)
				if(containsVertex(*points,  v->getAdj()->at(j).getDest())){
					if(UNDIRECTED_GRAPH)
						gv->addEdge(edgeID++, v->getInfo()->getID(), v->getAdj()->at(j).getDest()->getInfo()->getID(), EdgeType::UNDIRECTED);
					else
						gv->addEdge(edgeID++, v->getInfo()->getID(), v->getAdj()->at(j).getDest()->getInfo()->getID(), EdgeType::DIRECTED);
				}
		}
	}
	
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
	if(mainApp.getLast() != NULL){
		cout << "\n There is already a final point\n\n";
		return;
	}
	if(mainApp.getInitial() != NULL){
		cout << " Consider choosing one of the vertexes in the scc.txt file\n\n";
		ofstream out("scc.txt");
		printVertexIndex(mainApp.getMainGraph(), scc( mainApp.getMainGraph(), mainApp.getMainGraph()->findVertex(*mainApp.getInitial()), UNDIRECTED_GRAPH), out);
		out.close();
	}
	int finalID =  menuInput(question, 0, mainApp.getMainGraph()->getNumVertex() - 1);
	if(!mainApp.addLast(*(mainApp.getMainGraph()->getVertexSet().at(finalID)->getInfo())))
		cout << "\n Error adding final point\n\n";
	
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

bool DeliveryPlaceMenu(bool getVolume) {
	header("DELIVERY PLACE");

	std::cout << " CHOOSE A DELIVERY PLACE:" << endl << endl;

	vector<string> shopsOptions = {
	"   1 - Department Store\n",
	"   2 - Variety Store\n",
	"   3 - SuperMarket\n",
	"   4 - DoItYourself\n",
	"   5 - Convenience\n",
	"   6 - Clothes\n",
	"   7 - Hardware\n",
	"   8 - Furniture\n",
	"   9 - Eletronics\n",
	"   10 - Mobile Phone\n",
	"   11 - Shoes\n",
	"   12 - Alcohol\n"
	};

	bool existStore = false;
	for(unsigned int i = 0; i < _N_SHOPS_TYPE; i++)
		if(!mainApp.getSmallShopsByType(static_cast<map_info_t>(i)).empty()){
			existStore = true;
			cout << shopsOptions.at(i);
		}
	if(!existStore){
		cout << "\n There is no delivery place in this SCC\n\n";
		return false;
	}

	int option_number;

	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 12);
	bool valid = false;
	while(!valid){
		if(option_number == 0) return false;
		if(mainApp.getSmallShopsByType(static_cast<map_info_t>(option_number - 1)).empty()){
			cout << " There is no delivery place of that type in this SCC\n";
			option_number = menuInput(" Option ? ", 0, 12);
		}
		else{
			valid = true;
		}
	}

	Delivery newDelivery(mainApp.getRandomSmallShopByType(static_cast<map_info_t>(option_number - 1)));

	if(getVolume) 
		newDelivery.setVolume(menuInput(" Delivery Volume: ", 1, 200)); //TODO VER MELHOR MIN E MAX DE VOL

	mainApp.addDelivery(newDelivery);
	return true;
}

void Prob1Menu() {
	
	if(!DeliveryPlaceMenu(false))
		ProblemsMenu();

	header("ONE TRUCK - ONE DELIVERY");

	int option_number;

	std::cout << " CHOOSE AN ALGORITHM:" << endl << endl;

	std::cout << "   1 - Dijkstra Algorithm" << endl;
	std::cout << "   2 - A* Algorithm" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 2);


	Delivery delivery = mainApp.getDeliveries().at(0);
	vector<Vertex<MapInfo> *>  solutionPath;
	switch (option_number) {
		case 1 :
			solutionPath = bidirectionalDijkstra(mainApp.getSmallGraph(), *(mainApp.getInitial()), delivery.getDest(), *(mainApp.getLast()), UNDIRECTED_GRAPH);
			showPathGV(mainApp.getSmallGraph(), mainApp.getInitial(), mainApp.getLast(), mainApp.getDeliveriesInfo(), &solutionPath);
			break;
		case 2 :
			solutionPath = bidirectionalAStar(mainApp.getSmallGraph(), *(mainApp.getInitial()), delivery.getDest(), *(mainApp.getLast()), UNDIRECTED_GRAPH);
			showPathGV(mainApp.getSmallGraph(), mainApp.getInitial(), mainApp.getLast(), mainApp.getDeliveriesInfo(), &solutionPath);
			break;
		case 0 :
		default:
			break;
	}
	mainApp.clearDelivery();
	ProblemsMenu();
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
			*solutionPath = NearestNeighborEuclidean(graph, *mainApp.getInitial(), mainApp.getDeliveriesInfo(), *mainApp.getLast());
			showPathGV(graph, mainApp.getInitial(), mainApp.getLast(), mainApp.getDeliveriesInfo(), solutionPath);
			Prob2Menu();
			break;
		case 2 :
			*solutionPath = NearestNeighborFloyd(graph, *mainApp.getInitial(), mainApp.getDeliveriesInfo(), *mainApp.getLast());
			showPathGV(graph, mainApp.getInitial(), mainApp.getLast(), mainApp.getDeliveriesInfo(), solutionPath);
			Prob2Menu();
			break;
		case 0 :
			//std::system("cls");
			Prob2Menu();
			return;
		default:
			break;
	}
}

void Prob2Menu() {

	while (DeliveryPlaceMenu(false));
	if(mainApp.getDeliveries().empty())
		ProblemsMenu();

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
			break;
		case 2 :
			solutionPath = twoOptAlgorithm(mainApp.getSmallGraph(), *mainApp.getInitial(), *mainApp.getLast(), mainApp.getDeliveriesInfo());
			showPathGV(mainApp.getSmallGraph(), mainApp.getInitial(), mainApp.getLast(), mainApp.getDeliveriesInfo(), &solutionPath);
			break;
		case 0 :
			//std::system("cls");
			break;
		default:
			break;
	}
	mainApp.clearDelivery();
	ProblemsMenu();
}

void Prob3Menu() {

	while (DeliveryPlaceMenu(true));
	if(mainApp.getDeliveries().empty())
		ProblemsMenu();

	header("MULTIPLE TRUCKS - MULTIPLE DELIVERIES");

	//Distribuir mainApp.deliveries pelos camioes

	//Escolher algoritmo a usar

	//Aplicar esse algoritmo para a lista de deliveries de cada camiao
	
}

void ProblemsMenu() {
	header("PROBLEMS");

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - One Truck - One Delivery" << endl;
	std::cout << "   2 - One Truck - Multiple Deliveries" << endl;
	std::cout << "   3 - Mutiple Trucks - Multiple Deliveries" << endl;
	std::cout << "   4 - Show Smaller Graph" << endl;
	std::cout << "   0 - Go Back" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 4);

	switch (option_number)
	{
		case 1: 
			Prob1Menu();
			break;
		case 2:
			Prob2Menu();
			break;
		case 3:
			Prob3Menu();
			break;
		case 4:
			showGraph(mainApp.getSmallGraph(), mainApp.getInitial(), mainApp.getLast());
			ProblemsMenu();
			break;
		case 0:
			//std::system("cls");
			mainApp.removeSmallGraph();
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
		std::system("pause");
		PointMenu(initial);
		break;
	case 4:
		showPointGV(mainApp.getMainGraph(), initial);
		PointMenu(initial);
		break;
	case 0:
		std::system("cls");
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
	
	MapInfo * lastMI = mainApp.getLast();
	vector<Vertex<MapInfo> *> res;

	if(option_number != 0){
		// TODO: fazer aquela animacao dos 3 pontos
		cout << " Calculating..." << endl;

		res = scc(mainApp.getMainGraph(), mainApp.getMainGraph()->findVertex(*mainApp.getInitial()), UNDIRECTED_GRAPH);
	}

	switch (option_number)
	{
	case 1:
		printVertex(res, cout);
		std::system("pause");
		ConnectionMenu();
		break;
	case 2:
		showPathGV(mainApp.getMainGraph(), mainApp.getInitial(), &res);
		ConnectionMenu();
		break;
	case 3:
		if(lastMI == NULL)
			cout << " Final Vertex not define\n\n";
		else if(containsVertex(res, mainApp.getMainGraph()->findVertex(*lastMI)))
			cout << " The Initial and Final Points are connected\n\n";
		else
			cout << " There is no connection between the Initial and the Final Point\n\n";
		system("pause");
		MapOperationsMenu();
		break;
	case 0:
		std::system("cls");
		MapOperationsMenu();
		return;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void MapOperationsMenu(){
	header("MAP OPERATIONS");
	Graph<MapInfo> smallGraph;

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
			system("pause");
			MapOperationsMenu();
		}
		else
			ConnectionMenu();
		break;
	case 4:
		if(mainApp.getInitial() == NULL || mainApp.getLast() == NULL){
			cout << "\n You must first enter a intial and final point\n\n";
			system("pause");
			MapOperationsMenu();
		}
		else{
			cout << "\n Shrinking graph size...\n\n";
			try
			{
				smallGraph = shrinkGraph(mainApp.getMainGraph(), mainApp.getMainGraph()->findVertex(*(mainApp.getInitial())), mainApp.getMainGraph()->findVertex(*(mainApp.getLast())), UNDIRECTED_GRAPH);
				mainApp.addSmallGraph(&smallGraph);
				header("SOLVE PROBLEMS");
				ProblemsMenu();
			}
			catch(const std::exception& e)
			{
				std::cerr << " " << e.what() << '\n';
				system("pause");
				MapOperationsMenu();
			}
		}
		break;
	case 0:
		std::system("cls");
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
		buildGraph(*graph, "Aveiro", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Aveiro", graph);
		break;
	case 2:
		buildGraph(*graph, "Braga", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Braga", graph);		
		break;
	case 3:
		buildGraph(*graph, "Coimbra", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Coimbra", graph);		
		break;
	case 4:
		buildGraph(*graph, "Ermesinde", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Ermesinde", graph);		
		break;
	case 5:
		buildGraph(*graph, "Fafe", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Fafe", graph);
		break;
	case 6:
		buildGraph(*graph, "Gondomar", UNDIRECTED_GRAPH);	
		buildApplication(&mainApp, "Gondomar", graph);		
		break;
	case 7:
		buildGraph(*graph, "Lisboa", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Lisboa", graph);		
		break;
	case 8:
		buildGraph(*graph, "Maia", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Maia", graph);		
		break;
	case 9:
		buildGraph(*graph, "Porto", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Porto", graph);		
		break;
	case 10:
		buildGraph(*graph, "Portugal", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Portugal", graph);		
		break;
	case 11:
		buildGraph(*graph, "Viseu", UNDIRECTED_GRAPH);
		buildApplication(&mainApp, "Viseu", graph);		
		break;
	case 0:
		break;
    default:break;
    }
	std::system("cls");
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
			std::system("cls");
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
		std::system("cls");
		return;
    default:break;
    }
}

//=======================================================================================================================//

int main() {	
	std::system("title   SMART DELIVERY");

	InicialMenu();

	// mainApp.~Application();

	return 0;
}
