#include "Application.h"

using namespace std;

Application::Application() {
	mainGraph = NULL;
	smallGraph = NULL;

	initial = NULL;
	last = NULL;
};


Application::Application(Graph<MapInfo> * mainGraph): mainGraph(mainGraph) {};

// TODO: verificar
Application::~Application() {
	mainGraph->~Graph();
	smallGraph->~Graph();
	free(mainGraph);
	free(smallGraph);
}

const vector<MapInfo> & Application::getAllShopsByType(map_info_t shopType) const {
	if(shopType < _N_SHOPS_TYPE)
		return this->shops[shopType];
	throw invalid_argument("shopType must be less than " + _N_SHOPS_TYPE);
}

const std::vector<MapInfo> & Application::getSmallShopsByType(map_info_t shopType) const {
	if(shopType < _N_SHOPS_TYPE)
		return this->smallShops[shopType];
	throw invalid_argument("shopType must be less than " + _N_SHOPS_TYPE);
}


MapInfo Application::getRandomShopByType(map_info_t shopType)
{
	vector<MapInfo> typeShops = getAllShopsByType(shopType);
	return typeShops.at(rand() % typeShops.size());
}

MapInfo Application::getRandomSmallShopByType(map_info_t shopType){
	vector<MapInfo> typeShops = getSmallShopsByType(shopType);
	return typeShops.at(rand() % typeShops.size());
}


bool Application::addInitial(MapInfo initialPoint){
	if(this->initial != NULL)
		return false;
	Vertex<MapInfo> * initialV = this->mainGraph->findVertex(initialPoint);
	if(initialV == NULL)
		return false;
	initialV->getInfo()->setInitial();
	this->initial = initialV->getInfo();
	return true;
}

bool Application::addLast(MapInfo lastPoint){
	if(this->last != NULL)
		return false;
	Vertex<MapInfo> * finalV = this->mainGraph->findVertex(lastPoint);
	if(finalV == NULL)
		return false;
	finalV->getInfo()->setFinal();
	this->last = finalV->getInfo();
	return true;
}

bool Application::removeInitial(){
	if(this->initial == NULL)
		return true;
	Vertex<MapInfo> * initialV = this->mainGraph->findVertex( *(this->initial));
	if(initialV == NULL)
		return false;
	initialV->getInfo()->removeInitial();
	this->initial = NULL;
	return true;
}

bool Application::removeLast(){
	if(this->last == NULL)
		return true;
	Vertex<MapInfo> * finalV = this->mainGraph->findVertex( *(this->last));
	if(finalV == NULL)
		return false;
	finalV->getInfo()->removeInitial();
	this->last = NULL;
	return true;
}

void Application::addSmallGraph(Graph<MapInfo> * graph){
	this->smallGraph = graph;
	for(unsigned int i = 0; i < _N_SHOPS_TYPE; i++)
		for(unsigned int j = 0; j < this->shops[i].size(); j++)
			if(this->smallGraph->findVertex(this->shops[i].at(j)) != NULL)
				this->smallShops[i].push_back(this->shops[i].at(j));
}

void Application::addMainGraph(Graph<MapInfo> * mainGraph){
	this->mainGraph = mainGraph;
}



// A partir daqui
void Application::addDeposit(const MapInfo &info)
{
	deposits.push_back(info);
}

bool Application::addShop(const MapInfo &info, map_info_t shopType)
{
	if(_N_SHOPS_TYPE <= shopType)
		return false;
	
	shops[shopType].push_back(info);
	return true;
}

void Application::addDelivery(const MapInfo &info)
{
	deliveries.push_back(info);
}

bool Application::removeDelivery(const MapInfo &info)
{
	auto it = find(deliveries.begin(), deliveries.end(), info);
	if(it == deliveries.end())
		return false;
	deliveries.erase(it);
	return true;
}

void Application::clear(){
	free(this->mainGraph);
	this->mainGraph = NULL;
	free(this->smallGraph);
	this->smallGraph = NULL;

	free(this->initial);
	this->initial = NULL;
	free(this->last);
	this->last = NULL;

	deposits.clear();

	for(unsigned int i = 0; i < (unsigned int) _N_SHOPS_TYPE; i++)
		shops[i].clear();

	deliveries.clear();
}
