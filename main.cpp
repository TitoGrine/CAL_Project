#include <iostream>
#include "Graph/Graph.h"
#include "Utilities/parser.h"
#include "Interface/ConsoleFunctions.h"
#include "Interface/Input.h"
#include "GraphViewer/graphviewer.h"
#include "GraphViewer/utilities.h"


using namespace std;

void InicialMenu();

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
*  |          MENUS         |
*  |                        |
*  +------------------------+
*/

void MapMenu()
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
	Graph * graph = (Graph *)malloc(sizeof(Graph));
	GraphViewer * gv = (GraphViewer *)malloc(sizeof(GraphViewer));
	switch (option_number)
	{
	case 1:
		graph = buildGraph("Aveiro");
		cout << "\t" << graph->getTopBound() << endl << graph->getLeftBound() << "\t\t\t" << graph->getRightBound() << "\n\t" << graph->getBottomBound() << endl;
		gv = createGraphViewer(graph);
		gv->rearrange();
		getchar();
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		
		break;
	case 0:
		system("cls");
		mainHeader("Welcome to the Smart Delivery");
		InicialMenu();
		break;
    default:break;
    }
}

//-----------------------------------------------------------------------------------------------------------------------//

void InicialMenu()
{

	int option_number;

	std::cout << " OPTIONS:" << endl << endl;

	std::cout << "   1 - Choose Map" << endl;
	std::cout << "   0 - Exit" << endl << endl;

	option_number = menuInput(" Option ? ", 0, 1);

	switch (option_number)
	{
	case 1:
		header("CHOOSE MAP");
		MapMenu();
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
	mainHeader("Welcome to the Smart Delivery");


	InicialMenu();

	return 0;
}

