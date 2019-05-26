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

std::vector<Vertex<MapInfo> *> Truck::getPath() const
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