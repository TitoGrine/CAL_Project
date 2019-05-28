#pragma once

#include <vector>
#include <string>
#include "Delivery.h"
#include "../Graph/Graph.h"

/**
 * @brief Truck Class that contains usefull information about one truck like his id, deliveries and path
 * 
 */
class Truck {
    static int ID;
    int truckID;

	// Truck ID
    int capacity;

	// Vector of Deliveries
    std::vector<Delivery*> deliveries;

	// Final Path
    std::vector<Vertex<MapInfo> *> path;

    public:
		/**
		 * @brief Construct a new Truck object
		 * 
		 */
        Truck();

		/**
		 * @brief Construct a new Truck object
		 * 
		 * @param capacity Capacity of the new truck
		 */
        Truck(int capacity);

		/**
		 * @brief Construct a new Truck object
		 * 
		 * @param truck That we eant to initialize the new truck with
		 */
        Truck(const Truck & truck);

		/**
		 * @brief Get Truck ID
		 * 
		 * @return int Truck ID
		 */
        int getID() const;

		/**
		 * @brief Get the Truck Capacity
		 * 
		 * @return int Truck Capacity
		 */
        int getCapacity() const;

		/**
		 * @brief Get the Deliveries vector
		 * 
		 * @return const std::vector<Delivery*>& Vecotr of deliveries
		 */
        const std::vector<Delivery*> & getDeliveries() const;
		/**
		 * @brief Add a new delivery
		 * 
		 * @param delivery Delivery to be added
		 */
        void addDelivery(Delivery* delivery);

		/**
		 * @brief Get the Path
		 * 
		 * @return const std::vector<Vertex<MapInfo> *>& Vector of vertexes corresponding to the path
		 */
        const std::vector<Vertex<MapInfo> *> & getPath() const;

		/**
		 * @brief Set the Path vector
		 * 
		 * @param path New path to be set
		 */
        void setPath(std::vector<Vertex<MapInfo> *> path);

        bool operator<(const Truck & truck) const;
};

