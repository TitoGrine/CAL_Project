#pragma once

#include <vector>
#include <string>
#include "Delivery.h"
#include "../Graph/Graph.h"

class Truck {
    static int ID;
    int truckID;

    int capacity;
    int availableCapacity;

    std::string pathColor;

    std::vector<Delivery> deliveries;
    std::vector<Vertex<MapInfo> *> path;

    public:
        Truck();
        Truck(int capacity);

        int getID() const;
        int getCapacity() const;
        int getAvailableCapacity() const;

        std::string getPathColor() const;
        void setPathColor(std::string pathColor);

        bool addDelivery(const Delivery &delivery);
        std::vector<Delivery> getDeliveries() const;
        void setDeliveries(const std::vector<Delivery> &deliveries);

        std::vector<Vertex<MapInfo> *> getPath() const;
        void setPath(std::vector<Vertex<MapInfo> *> path);
};

