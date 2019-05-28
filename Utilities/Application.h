/*
 * Application.h
 */
#pragma once
/************************* Application  **************************/

#include "../Graph/Graph.h"
#include "MapInfo.h"
#include "Truck.h"
#include "Delivery.h"
#include <vector>
#include <string>
#include <queue>

template <class T> class Graph;

struct CmpTruckPtrs
{
    bool operator()(const Truck* lhs, const Truck* rhs) const
    {
        return *lhs < *rhs;
    }
};

class Application {
	Graph<MapInfo> * mainGraph;
	Graph<MapInfo> * smallGraph;

	MapInfo * initial;
	MapInfo * last;

	std::vector<MapInfo> deposits;

	std::vector<MapInfo> shops[_N_SHOPS_TYPE];

	std::vector<MapInfo> smallShops[_N_SHOPS_TYPE];

	std::vector<Delivery*> deliveries;

	std::priority_queue<Truck*, std::vector<Truck*>, CmpTruckPtrs> trucks;

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
	std::vector < MapInfo> getDeliveriesInfo() const;
	const std::vector < Delivery*> & getDeliveries() const;  
	const std::priority_queue<Truck*, std::vector<Truck*>, CmpTruckPtrs> & getTrucks() const;

	void addDeposit(const MapInfo &info);
	bool addShop(const MapInfo &info, map_info_t tagNum);
	void addTruck(const Truck &truck);

	void addSmallGraph(Graph<MapInfo> * graph);
	void addMainGraph(Graph<MapInfo> * mainGraph);
	
	void addDelivery(Delivery* delivery);
	void clearDeliveries();
	void clearAllDeliveries();

	void popTruck();

	void clear();
	void removeSmallGraph();


	~Application();
};
