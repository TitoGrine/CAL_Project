/*
 * Application.h
 */
#pragma once
/************************* Application  **************************/

#include "../Graph/Graph.h"
#include "MapInfo.h"
#include <vector>
#include <string>

template <class T> class Graph;

enum map_info_t {
	DEPARTMENT_STORE,
	VARIETY_STORE,
	SUPERMARKET,
	DIY,
	CONVENIENCE,
	CLOTHES,
	HARDWARE,
	FURNITURE,
	ELECTRONICS,
	MOBILE_PHONE,
	SHOES,
	ALCOHOL,
	_N_SHOPS_TYPE,
	DEPOSIT,
	OTHER	
};

class Application {
	Graph<MapInfo> * mainGraph;
	Graph<MapInfo> * smallGraph;

	MapInfo * initial;
	MapInfo * last;

	std::vector<MapInfo> deposits;

	std::vector<MapInfo> shops[_N_SHOPS_TYPE];

	std::vector<MapInfo> smallShops[_N_SHOPS_TYPE];


	std::vector<MapInfo> deliveries;

public:
	Application();
	Application(Graph<MapInfo> * mainGraph);

	Graph<MapInfo> * getMainGraph() { return this->mainGraph; };
	Graph<MapInfo> * getSmallGraph() { return this->smallGraph; };

	MapInfo * getInitial() { return this->initial; };
	MapInfo * getLast() { return this->last; };

	bool addInitial(MapInfo initialPoint);
	bool addLast(MapInfo lastPoint);
	bool removeInitial();
	bool removeLast();
	

	const std::vector<MapInfo> & getDeposits() const { return this->deposits; };
	const std::vector<MapInfo> & getAllShopsByType(map_info_t shopType) const;
	const std::vector<MapInfo> & getSmallShopsByType(map_info_t shopType) const;
	MapInfo getRandomShopByType(map_info_t shopType);
	MapInfo getRandomSmallShopByType(map_info_t shopType);
	const std::vector < MapInfo> & getDeliveries() const { return this->deliveries; };

	void addDeposit(const MapInfo &info);
	bool addShop(const MapInfo &info, map_info_t tagNum);

	void addSmallGraph(Graph<MapInfo> * graph);
	void addMainGraph(Graph<MapInfo> * mainGraph);
	
	void addDelivery(const MapInfo &info);
	bool removeDelivery(const MapInfo &info);
	void clearDelivery() { this->deliveries.clear(); };

	void clear();
	void freeSmallGraph();


	~Application();
};
