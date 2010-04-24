#ifndef LINE_HPP
#define LINE_HPP

#include "Gosu.hpp"
#include "Building.hpp"
#include "RessourceArea.hpp"
#include "Ressource.hpp"


struct RessourceOnLine
{
	RessourceOnLine(Point2D position, RessourceType type)
		: position(position), type(type)
	{

	};

	Point2D position;
	RessourceType type;
};

class Line
{
	public:
		// Powerline
		Gosu::Graphics* graphics;
		Building *start, *end;
		int type;

		// Transportline
		vector<RessourceOnLine> ressources;
		double speed;

		Line(Gosu::Graphics* graphics, int type, double speed = 2)
			: graphics(graphics), type(type), speed(speed)
		{
			
		}

		void draw(int x, int y)
		{
			Gosu::Color c1 = Gosu::Colors::red;
			if(this->type == 1) c1 = Gosu::Colors::aqua;
			Gosu::Color c2 = c1;
			c2.setAlpha(10);

			graphics->drawLine(this->start->x + x, this->start->y + y, c2, this->end->x + x, this->end->y + y, c1, 11);	
		}

		void update()
		{
			// Powerline
			if(type == 0)
			{
				int neededEnergy = this->end->energyRequirement - this->end->energyIn;
				int suppliedEnergy = this->start->energyOut;

				if(suppliedEnergy == 0 || neededEnergy < 0) return;


				if(neededEnergy > suppliedEnergy)
				{
					this->end->energyIn += this->start->energyOut;
					this->start->energyOut = 0;
				}
				else
				{
					this->start->energyOut -= neededEnergy;
					this->end->energyIn += neededEnergy;
				}
			}
			else // Transportline
			{
				// transport all items one step further
				for(vector<RessourceOnLine>::iterator it = this->ressources.begin(); it != this->ressources.end(); ++it)
				{
					RessourceOnLine curRes = (*it);
					
					// check if we are there!
					
				}
			}
		}

};

#endif