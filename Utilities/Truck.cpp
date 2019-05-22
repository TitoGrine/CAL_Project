#include "Truck.h"

int Truck::ID = 0;

Truck::Truck(int capacity): capacity(capacity) { 
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

std::string Truck::getPathColor() const 
{ 
    return this->pathColor;   
}

void Truck::setPathColor(std::string pathColor) 
{ 
    this->pathColor = pathColor; 
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