#include "Truck.h"

int Truck::ID = 0;

Truck::Truck(int capacity): capacity(capacity) { 
    this->truckID = ID++;
}

Truck::Truck(const Truck & truck)
{
    this->truckID = truck.getID();
    this->capacity = truck.getCapacity();
}

int Truck::getID() const 
{ 
    return this->truckID; 
}

int Truck::getCapacity() const 
{
    return this->capacity; 
}

const std::vector<Vertex<MapInfo> *> & Truck::getPath() const
{
    return this->path;
}

void Truck::setPath(std::vector<Vertex<MapInfo> *> path)
{
    this->path = path;
}

bool Truck::operator<(const Truck &truck) const
{
    return (this->capacity > truck.getCapacity());
}