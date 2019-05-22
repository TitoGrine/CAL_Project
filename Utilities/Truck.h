#pragma once

#include <vector>
#include <string>
#include "Delivery.h"
#include "../Graph/Graph.h"

class Truck {
    static int ID;
    int truckID;

    int capacity;

    std::string pathColor;

    std::vector<Delivery> deliveries;
    std::vector<Vertex<MapInfo> *> path;

    public:
        Truck();
        Truck(int capacity);

        int getID() const;
        int getCapacity() const;

        std::string getPathColor() const;
        void setPathColor(std::string pathColor);

        std::vector<Delivery> getDeliveries() const;
        void setDeliveries(const std::vector<Delivery> &deliveries);

        std::vector<Vertex<MapInfo> *> getPath() const;
        void setPath(std::vector<Vertex<MapInfo> *> path);
};

