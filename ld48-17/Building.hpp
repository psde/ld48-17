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
	Factory,
	Spaceport
};


class Building
{
	public:

		static int getBuildingType(BuildingType type)
		{
			switch(type)
			{
				case EnergyCollector:
					return 0;

				case Mine:
					return 1;

				case Depot:
					return 2;

				case Factory:
					return 3;

				case Spaceport:
					return 4;
			}
		}
		
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
		int wantsRes[3];

		// factory



		Building(double x, double y, BuildingType type, RessourceArea* area = 0)
			: x(x), y(y), type(type), energyIn(0), energyOut(-1), energyRequirement(-1), energySupplied(0), disabled(false), area(area), tick(0)
		{
			this->internalDepot[0] = 0;
			this->internalDepot[1] = 0;
			this->internalDepot[2] = 0;

			this->wantsRes[0] = 0;
			this->wantsRes[1] = 0;
			this->wantsRes[2] = 0;

			if(type == Mine) {
				energyRequirement = 10;
				if(this->area != 0)
				{
					switch(this->area->type)
					{
						case Ore:
							this->maxTick = 50;
						
						case Silicon:
							this->maxTick = 50;

						case Uranium:
							this->maxTick = 50;
					}
				}
			}

			if(type == Depot)
			{
				energyRequirement = 2;
				this->wantsRes[0] = -1;
				this->wantsRes[1] = -1;
				this->wantsRes[2] = -1;
			}

			if(type == Factory)
			{
				energyRequirement = 25;
				this->wantsRes[2] = 10; // testing only
			}

			if(type == Spaceport)
			{
				energyRequirement = 75;
			}
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