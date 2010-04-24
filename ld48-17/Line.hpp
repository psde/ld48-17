#ifndef LINE_HPP
#define LINE_HPP

#include "Gosu.hpp"
#include "Building.hpp"

class Line
{
	public:
		Gosu::Graphics* graphics;
		Building *start, *end;
		int type;

		Line(Gosu::Graphics* graphics, int type)
			: graphics(graphics), type(type)
		{
			
		}

		void draw(int x, int y)
		{
			Gosu::Color c1 = Gosu::Colors::red;
			if(this->type == 1) c1 = Gosu::Colors::aqua;
			Gosu::Color c2 = c1;
			c2.setAlpha(120);

			graphics->drawLine(this->start->x + x, this->start->y + y, c2, this->end->x + x, this->end->y + y, c1, 11);	
		}

		void update()
		{
			if(type == 0)
			{
				int neededEnergy = this->end->energyRequirement;
				int suppliedEnergy = this->start->energyOut;

				if(suppliedEnergy == 0) return;

				if(neededEnergy > suppliedEnergy)
				{
					this->end->energyIn = this->start->energyOut;
					this->start->energyOut = 0;
				}
				else
				{
					this->start->energyOut -= neededEnergy;
					this->end->energyIn = neededEnergy;
				}
			}
			else
			{
				// transport line
			}
		}

};

#endif