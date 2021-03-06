#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Gosu.hpp"
#include "Ressource.hpp"
#include "RessourceArea.hpp"
#include "Unit.hpp"

enum BuildingType
{
	EnergyCollector,
	Mine,
	Depot,
	Factory,
	Spaceport
};


enum BuildingUpdateResult
{
	BuildingNothingSpecial,
	BuildingFactoryFinished
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

		static int* getBuildingCost(BuildingType type)
		{
			int* foo = new int[3];

			switch(type)
			{
				case EnergyCollector:
					foo[0] = 30;
					foo[1] = 10;
					foo[2] = 0;
					break;

				case Mine:
					foo[0] = 20;
					foo[1] = 0;
					foo[2] = 0;
					break;

				case Depot:
					foo[0] = 10;
					foo[1] = 10;
					foo[2] = 0;
					break;

				case Factory:
					foo[0] = 70;
					foo[1] = 25;
					foo[2] = 15;
					break;

				case Spaceport:
					foo[0] = 100;
					foo[1] = 40;
					foo[2] = 30;
					break;
			}
			return foo;
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

		UnitType unitInBuild;
		int clusterMod;



		Building(double x, double y, BuildingType type, RessourceArea* area = 0)
			: x(x), y(y), type(type), energyIn(0), energyOut(-1), energyRequirement(-1), energySupplied(0), disabled(false), area(area), tick(0), maxTick(0), unitInBuild(NoUnit), clusterMod(0)
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
							this->maxTick = 200;
							break;
						
						case Silicon:
							this->maxTick = 400;
							break;

						case Uranium:
							this->maxTick = 800;
							break;
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
				maxTick = -1;
				//this->wantsRes[2] = 10; // testing only
			}

			if(type == Spaceport)
			{
				energyRequirement = 75;
			}
		}

		BuildingUpdateResult update()
		{
			if(type == EnergyCollector)
			{
				energyOut = 30;
			}
			else if(type == Mine)
			{
				if(!disabled && energyIn >= energyRequirement && this->area != 0)
				{
					if(this->area->availableTons > 0)
					{
						tick++;
						if(tick >= maxTick)
						{
							// ressource ready!
							this->internalDepot[this->area->type]++;
							this->area->availableTons--;
							tick = 0;
						}
					}
				}
			}
			else if(type == Factory)
			{
				if(this->unitInBuild != NoUnit && energyIn >= energyRequirement)
				{
					if(this->wantsRes[0] == 0 && this->wantsRes[1] == 0 && this->wantsRes[2] == 0)
					{
						if(maxTick == -1)
						{
							this->maxTick = Unit::getUnitBuildTime(this->unitInBuild);
							this->tick = 0;
						}else
						{
							this->tick++;
							if(this->tick >= maxTick)
							{
								this->maxTick = -1;
								return BuildingFactoryFinished;
							}
						}
					}
				}
			}

			return BuildingNothingSpecial;
		};
};


#endif