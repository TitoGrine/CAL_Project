#include "Truck.h"

int Truck::ID = 0;

Truck::Truck(int capacity): capacity(capacity), availableCapacity(capacity) { 
    this->truckID = ID++;
}

int Truck::getID() const 
{ 
    return this->truckID; 
}

int Truck::getCapacity() const 
{
    return this->capacity; 
}

int Truck::getAvailableCapacity() const
{
    return this->availableCapacity;
}

std::string Truck::getPathColor() const 
{ 
    return this->pathColor;   
}

void Truck::setPathColor(std::string pathColor) 
{ 
    this->pathColor = pathColor; 
}

bool Truck::addDelivery(const Delivery &delivery)
{
    int newAvailableCapacity = this->availableCapacity - delivery.getVolume();

    if(newAvailableCapacity < 0) return false;

    this->deliveries.push_back(delivery);
    this->availableCapacity = newAvailableCapacity;
    return true;
}

std::vector<Delivery> Truck::getDeliveries() const
{
    return this->deliveries;
}

void Truck::setDeliveries(const std::vector<Delivery> &deliveries)
{
    this->deliveries = deliveries;
}

std::vector<Vertex<MapInfo> *> Truck::getPath() const
{
    return this->path;
}

void Truck::setPath(std::vector<Vertex<MapInfo> *> path)
{
    this->path = path;
}