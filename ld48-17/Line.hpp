#ifndef LINE_HPP
#define LINE_HPP

#include "Gosu.hpp"
#include "Building.hpp"
#include "RessourceArea.hpp"
#include "Ressource.hpp"
#include "RessourceRenderer.hpp"


struct RessourceOnLine
{
	RessourceOnLine(Point2D position, RessourceType type)
		: position(position), type(type)
	{

	};

	RessourceOnLine(Point2D position, int type)
		: position(position)
	{
		switch(type)
		{
			case 0:
				this->type = Ore;
				break;

			case 1:
				this->type = Silicon;
				break;

			case 2:
				this->type = Uranium;
				break;

		}
	};

	Point2D position;
	RessourceType type;
};

class Line
{
	public:
		Gosu::Graphics* graphics;
		RessourceRenderer* resRenderer;

		Building *start, *end;
		int type;

		// Transportline
		vector<RessourceOnLine> ressources;
		double speed;
		int timeout;
		int tick;

		Line(Gosu::Graphics* graphics, RessourceRenderer* resRenderer, int type, double speed = 0.4, int timeout = 70)
			: graphics(graphics), resRenderer(resRenderer), type(type), speed(speed), tick(timeout), timeout(timeout)
		{
			
		}

		void draw(int x, int y)
		{
			Gosu::Color c1 = Gosu::Colors::red;
			if(this->type == 1) c1 = Gosu::Colors::aqua;
			Gosu::Color c2 = c1;
			c2.setAlpha(10);

			graphics->drawLine(this->start->x + x, this->start->y + y, c2, this->end->x + x, this->end->y + y, c1, 11);	

			if(type == 1)
			{
				for(vector<RessourceOnLine>::iterator it = this->ressources.begin(); it != this->ressources.end(); ++it)
				{
					RessourceOnLine curRes = (*it);

					resRenderer->draw(curRes.position.x + x - 10, curRes.position.y + y - 10, 12, curRes.type);					
				}
			}
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
				for(vector<RessourceOnLine>::iterator it = this->ressources.begin(); it != this->ressources.end(); )
				{
					RessourceOnLine curRes = (*it);


					double a = this->end->x - this->start->x;
					double b = this->end->y - this->start->y;
					double angle = atan2(b, a);

					(*it).position.x += cos(angle) * speed;
					(*it).position.y += sin(angle) * speed;

					// check if we are there!
					
					if(Gosu::distance((*it).position.x, (*it).position.y, this->end->x, this->end->y) < 10)
					{
						it = this->ressources.erase(it);
						this->end->internalDepot[curRes.type]++;
					}
					else
					{
						it++;
					}

				}

				if(this->tick >= this->timeout)
				{
					for(int i = 0; i < 3; i++)
					{
						if(this->start->internalDepot[i] > 0 && (this->end->wantsRes[i] == -1 || this->end->wantsRes[i] > 0))
						{
							this->ressources.push_back(RessourceOnLine(Point2D(this->start->x, this->start->y), i));
							this->start->internalDepot[i]--;
							if(this->end->wantsRes[i] > 0) this->end->wantsRes[i]--;
							this->tick = 0;
							break;
						}
					}
					
				}
				else
				{
					this->tick++;
				}
			}
		}

};

#endif