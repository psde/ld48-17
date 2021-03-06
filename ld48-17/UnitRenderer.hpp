#ifndef UNITRENDERER_HPP
#define UNITRENDERER_HPP


#include "Gosu.hpp"
#include "Unit.hpp"

class UnitRenderer
{
	public:
		Gosu::Graphics* graphics;
		Gosu::Image* backdrop;
		Gosu::Image* backdrop_white;
		Gosu::Image* scout;
		Gosu::Image* colo;
		Gosu::Image* cargo;


		UnitRenderer(Gosu::Graphics* graphics)
			: graphics(graphics)
		{
			this->backdrop = new Gosu::Image(*graphics, L"data/units/backdrop.png");
			this->backdrop_white = new Gosu::Image(*graphics, L"data/units/backdrop_white.png");
			this->scout = new Gosu::Image(*graphics, L"data/units/scout.png");
			this->colo = new Gosu::Image(*graphics, L"data/units/colo.png");
			this->cargo = new Gosu::Image(*graphics, L"data/units/cargo.png");
		}

		void drawUnit(int x, int y, int z, Unit* unit, bool selected=false, int sX=0, int sY=0)
		{

			Gosu::Color c = Gosu::Colors::white;
			switch(unit->order)
			{
				case DoMove:
					c = Gosu::Colors::green;
					break;

				case DoSpecial:
					c = Gosu::Colors::red;
					break;
			}



			if(selected)
			{
				this->backdrop_white->draw(x, y, z, 1, 1, Gosu::Colors::cyan);

				// show targetX/targetY
				int fX = unit->x - x;
				int fY = unit->y - y;
				if(unit->order != DoNothing)
				{
					this->graphics->drawLine(x+20, y+20, Gosu::Colors::white, unit->targetX + 20 - sX, unit->targetY + 20 - sY, c, z);
				}
			}
			else
			{
				this->backdrop_white->draw(x, y, z, 1, 1, c);
			}

			switch(unit->type)
			{
				case Scout:
					this->scout->draw(x, y, z+1);
					break;

				case Colo:
					this->colo->draw(x, y, z+1);
					break;

				case Cargo:
					this->cargo->draw(x, y, z+1);
					break;
			}
		}


		void drawUnitProp(int x, int y, int z, UnitType type, double factor = 1)
		{
			this->backdrop_white->draw(x, y, z, factor, factor);
			switch(type)
			{
				case Scout:
					this->scout->draw(x, y, z+1, factor, factor);
					break;

				case Colo:
					this->colo->draw(x, y, z+1, factor, factor);
					break;

				case Cargo:
					this->cargo->draw(x, y, z+1, factor, factor);
					break;
			}
		}
};

#endif