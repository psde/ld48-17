#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Gosu.hpp"
#include "Ressource.hpp"

enum BuildingType
{
	EnergyCollector,
	Mine,
	Depot
};

class Building
{
	public:
		
		BuildingType type;

		double x, y;
		double energyIn, energyOut;
		Ressource transportIn, transportOut;

		Building(double x, double y, BuildingType type)
			: x(x), y(y), type(type)
		{

		}

		void update()
		{
			
		};
};


#endif