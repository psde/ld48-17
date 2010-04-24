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
		double energyRequirement, energySupplied;
		Ressource transportIn, transportOut;

		Building(double x, double y, BuildingType type)
			: x(x), y(y), type(type), energyIn(0), energyOut(0), energyRequirement(0), energySupplied(0)
		{
			if(type == Mine) energyRequirement = 10;
			if(type == Depot) energyRequirement = 2;
		}

		void update()
		{
			if(type == EnergyCollector)
			{
				energyOut = 20;
			}else{
				energySupplied = 0;

				int dif = energyIn - energyRequirement;
				if(dif < 0)
				{
					energyOut = 0;
					energySupplied -= energyIn;
				}
				else
				{
					energySupplied = 0;
					energyOut = dif;
				}
					
			}
		};
};


#endif