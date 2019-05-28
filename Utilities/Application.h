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

/**
 * @brief Struct that allows truck pointer comparation in order to store them in a priority queue
 * 
 */
struct CmpTruckPtrs
{
    bool operator()(const Truck* lhs, const Truck* rhs) const
    {
        return *lhs < *rhs;
    }
};

/**
 * @brief Main Application Class
 * Class that has the information needed to control the flow of the interface
 * This class can also represent the Delivery Company
 * 
 */
class Application {
	// Main Graph corresponding to the whole selected city
	Graph<MapInfo> * mainGraph;
	// Smaller graph corresponding to the SCC containing the initial vertex
	Graph<MapInfo> * smallGraph;

	// Initial Vertex
	MapInfo * initial;
	// Final Vertex
	MapInfo * last;

	// List with all the possible deposits (initial vertexes)
	std::vector<MapInfo> deposits;
	// Array of vector with all the shops from the tag file
	std::vector<MapInfo> shops[_N_SHOPS_TYPE];
	// Array of vector with all the shops from the tag file present in the smaller graph
	std::vector<MapInfo> smallShops[_N_SHOPS_TYPE];
	// List of all the deliveries
	std::vector<Delivery*> deliveries;
	// Priority queue with all the trucks that the company has
	std::priority_queue<Truck*, std::vector<Truck*>, CmpTruckPtrs> trucks;

public:
	/**
	 * @brief Construct a new Application object
	 * 
	 */
	Application();
	/**
	 * @brief Construct a new Application object
	 * 
	 * @param mainGraph Graph of the whole city
	 */
	Application(Graph<MapInfo> * mainGraph);

	/**
	 * @brief Get the Main Graph object
	 * 
	 * @return Graph<MapInfo>* Main Graph corresponding to an entire city
	 */
	Graph<MapInfo> * getMainGraph() { return this->mainGraph; };
	/**
	 * @brief Get the Small Graph object
	 * 
	 * @return Graph<MapInfo>*  Small Graph corresponding to a SCC within the MainGraph
	 */
	Graph<MapInfo> * getSmallGraph() { return this->smallGraph; };

	/**
	 * @brief Get the Initial MapInfo object
	 * 
	 * @return MapInfo* Initial Vertex Details
	 */
	MapInfo * getInitial() { return this->initial; };
	/**
	 * @brief Get the Last object
	 * 
	 * @return MapInfo* Last Vertex Details
	 */
	MapInfo * getLast() { return this->last; };

	/**
	 * @brief Add Intial Point
	 * 
	 * @param initialPoint MapInfo representing the initial MapInfo
	 * @return true If the operation was successfull
	 * @return false If there was already an initial Point or the specified MapInfo doesn't exists
	 */
	bool addInitial(MapInfo initialPoint);
	/**
	 * @brief Add Final Point
	 * 
	 * @param lastPoint MapInfo representing the final MapInfo
	 * @return true If the operation was successfull
	 * @return false If there was already a final Point or the specified MapInfo doesn't exists
	 */
	bool addLast(MapInfo lastPoint);
	/**
	 * @brief Removes Intial point
	 * 
	 * @return true If the Intial Vertex was successfully unset
	 * @return false If initial MapInfo private parameter was not found in the graph
	 */
	bool removeInitial();
	/**
	 * @brief Removes Final point
	 * 
	 * @return true If the Final Vertex was successfully unset
	 * @return false If last MapInfo private parameter was not found in the graph
	 */
	bool removeLast();
	
	/**
	 * @brief Get the Deposits vector
	 * 
	 * @return const std::vector<MapInfo>&  All the possible Deposits
	 */
	const std::vector<MapInfo> & getDeposits() const { return this->deposits; };
	/**
	 * @brief Get the All Shops of a Certain Type present in the city graph
	 * 
	 * @param shopType map_info_t specifying the desired type of shop
	 * @return const std::vector<MapInfo>& All shops of a certain type
	 */
	const std::vector<MapInfo> & getAllShopsByType(map_info_t shopType) const;
	/**
	 * @brief Get the All Shops of a Certain Type present in the small graph
	 * 
	 * @param shopType map_info_t specifying the desired type of shop
	 * @return const std::vector<MapInfo>& All shops of a certain type present in the small graph
	 */
	const std::vector<MapInfo> & getSmallShopsByType(map_info_t shopType) const;
	/**
	 * @brief Get the Random Shop of a Certain Type present in the city graph
	 * 
	 * @param shopType map_info_t specifying the desired type of shop
	 * @return MapInfo Random Shop of the specified present in the city graph
	 */
	MapInfo getRandomShopByType(map_info_t shopType);
	/**
	 * @brief Get the Random Shop of a Certain Type present in the small graph
	 * 
	 * @param shopType map_info_t specifying the desired type of shop
	 * @return MapInfo Random Shop of the specified present in the small graph
	 */
	MapInfo getRandomSmallShopByType(map_info_t shopType);
	/**
	 * @brief Get the MapInfo of all the Deliveries
	 * 
	 * @return std::vector < MapInfo> Deliveries information
	 */
	std::vector < MapInfo> getDeliveriesInfo() const;
	/**
	 * @brief Get the Deliveries private parameter
	 * 
	 * @return const std::vector < Delivery*>&  Deliveries vector
	 */
	const std::vector < Delivery*> & getDeliveries() const;
	/**
	 * @brief Get the Trucks private parameter
	 * 
	 * @return const std::priority_queue<Truck*, std::vector<Truck*>, CmpTruckPtrs>& Truck queue
	 */
	const std::priority_queue<Truck*, std::vector<Truck*>, CmpTruckPtrs> & getTrucks() const;

	/**
	 * @brief Add new Deposit to the Deposits vector
	 * 
	 * @param info MapInfo corresponding to the new deposit
	 */
	void addDeposit(const MapInfo &info);
	/**
	 * @brief Add new Shop to the shops private parameter
	 * 
	 * @param info MapInfo of the new shop
	 * @param tagNum map_info_t corresponding to the type of the shop
	 * @return true If the shpo was added with success
	 * @return false If the map_info_t is invalid
	 */
	bool addShop(const MapInfo &info, map_info_t tagNum);
	/**
	 * @brief Add new truck to trucks queue
	 * 
	 * @param truck New truck to be added
	 */
	void addTruck(const Truck &truck);

	/**
	 * @brief Add small graph that represents a scc from the mainGraph
	 * 
	 * @param graph SCC of the main Graph containing the initail vertex
	 */
	void addSmallGraph(Graph<MapInfo> * graph);
	/**
	 * @brief Add main graph that represents a city map
	 * 
	 * @param mainGraph Graph representing a city map
	 */
	void addMainGraph(Graph<MapInfo> * mainGraph);
	
	/**
	 * @brief Add new delivey to the deliveries vector
	 * 
	 * @param delivery New Delivey to be added
	 */
	void addDelivery(Delivery* delivery);
	/**
	 * @brief Removes from the deliveries vector, the ones that are already delivered
	 * 
	 */
	void clearDeliveries();
	/**
	 * @brief Clear deliveries vector
	 * 
	 */
	void clearAllDeliveries();

	/**
	 * @brief Pop top of the trucks queue
	 * 
	 */
	void popTruck();

	/**
	 * @brief Clears and Frees all the Applicaion private parameters
	 * 
	 */
	void clear();
	/**
	 * @brief Removes Samll graph
	 * 
	 */
	void removeSmallGraph();

	/**
	 * @brief Destroy the Application object
	 * 
	 */
	~Application();
};
