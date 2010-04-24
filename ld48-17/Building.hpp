#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Gosu.hpp"
#include "Ressource.hpp"
#include "RessourceArea.hpp"

enum BuildingType
{
	EnergyCollector,
	Mine,
	Depot,
	Factory
};

class Building
{
	public:
		
		BuildingType type;

		double x, y;
		double energyIn, energyOut;
		double energyRequirement, energySupplied;
		Ressource transportIn, transportOut;
		RessourceArea* area;
		bool disabled;

		int tick;
		int maxTick;
		int internalDepot[3];

		Building(double x, double y, BuildingType type, RessourceArea* area = 0)
			: x(x), y(y), type(type), energyIn(0), energyOut(-1), energyRequirement(-1), energySupplied(0), disabled(false), area(area), tick(0)
		{
			this->internalDepot[0] = 0;
			this->internalDepot[1] = 0;
			this->internalDepot[2] = 0;

			if(type == Mine) {
				energyRequirement = 10;
				if(this->area != 0)
				{
					switch(this->area->type)
					{
						case Ore:
							this->maxTick = 200;
						
						case Silicon:
							this->maxTick = 100;

						case Uranium:
							this->maxTick = 300;
					}
				}
			}

			if(type == Depot) energyRequirement = 2;
			if(type == Factory) energyRequirement = 25;
		}

		void update()
		{
			if(type == EnergyCollector)
			{
				energyOut = 20;
			}
			else if(type == Mine)
			{
				if(!disabled && energyIn == energyRequirement && this->area != 0)
				{
					if(this->area->availableTons > 0)
					{
						tick++;
						if(tick == maxTick)
						{
							// ressource ready!
							this->internalDepot[this->area->type]++;
							tick = 0;
						}
					}
				}
			}
		};
};


#endif