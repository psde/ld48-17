#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Gosu.hpp"
#include "Ressource.hpp"

class Building
{
	public:
		
		double type;

		double x, y;
		double energyIn, energyOut;
		Ressource transportIn, transportOut;

		Building(double x, double y)
			: x(x), y(y)
		{

		}
};


#endif