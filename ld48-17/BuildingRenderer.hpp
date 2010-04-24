#ifndef BUILDINGRENDERER_HPP
#define BUILDINGRENDERER_HPP

#include "Gosu.hpp"
#include "Building.hpp"

class BuildingRenderer
{
	private:
		Gosu::Graphics* graphics;

		Gosu::Image* backdrop;
		Gosu::Image* energy;
		Gosu::Image* depot;
		Gosu::Image* mine;

	public:
		BuildingRenderer(Gosu::Graphics* graphics)
			: graphics(graphics)
		{
			this->backdrop = new Gosu::Image(*graphics, L"data/buildings/backdrop.png");
			this->energy = new Gosu::Image(*graphics, L"data/buildings/energy.png");
			this->depot = new Gosu::Image(*graphics, L"data/buildings/depot.png");
			this->mine = new Gosu::Image(*graphics, L"data/buildings/mine.png");
		};

		void draw(Building &build, int x, int y, int z, int status=0)
		{
			Gosu::Color c = Gosu::Colors::white;

			if(status == 1) c = Gosu::Colors::red;
			if(status == 2) c = Gosu::Colors::green;

			this->backdrop->draw(x, y, z, 1, 1, c);
			switch(build.type)
			{
				case EnergyCollector:
					this->energy->draw(x, y, z, 1, 1, c);
					break;
				case Mine:
					this->mine->draw(x, y, z, 1, 1, c);
					break;
				case Depot:
					this->depot->draw(x, y, z, 1, 1, c);
					break;
			};
		}

};

#endif