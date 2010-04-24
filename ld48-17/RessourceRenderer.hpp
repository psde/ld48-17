#ifndef RESSOURCERENDERER_HPP
#define RESSOURCERENDERER_HPP

#include "Gosu.hpp"
#include "Ressource.hpp"

class RessourceRenderer
{
	private:
		Gosu::Graphics* graphics;

		Gosu::Image *ore, *uranium, *silicon;


	public:
		RessourceRenderer(Gosu::Graphics* graphics)
			: graphics(graphics)
		{
			this->ore = new Gosu::Image(*graphics, L"data/ressources/ore.png");
			this->uranium = new Gosu::Image(*graphics, L"data/ressources/uranium.png");
			this->silicon = new Gosu::Image(*graphics, L"data/ressources/silicon.png");
		}

		void draw(int x, int y, int z, RessourceType type)
		{
			switch(type)
			{
				case Ore:
					this->ore->draw(x, y, z);
					break;

				case Uranium:
					this->uranium->draw(x, y, z);
					break;

				case Silicon:
					this->silicon->draw(x, y, z);
					break;
			}
		}

};


#endif