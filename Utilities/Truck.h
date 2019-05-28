#pragma once

#include <vector>
#include <string>
#include "Delivery.h"
#include "../Graph/Graph.h"

class Truck {
    static int ID;
    int truckID;

    int capacity;

    std::vector<Delivery*> deliveries;

    std::vector<Vertex<MapInfo> *> path;

    public:
        Truck();
        Truck(int capacity);
        Truck(const Truck & truck);

        int getID() const;
        int getCapacity() const;

        const std::vector<Delivery*> & getDeliveries() const;
        void addDelivery(Delivery* delivery);

        const std::vector<Vertex<MapInfo> *> & getPath() const;
        void setPath(std::vector<Vertex<MapInfo> *> path);

        bool operator<(const Truck & truck) const;
};

