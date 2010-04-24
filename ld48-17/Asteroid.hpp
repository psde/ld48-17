#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Gosu.hpp"
#include "RessourceArea.hpp"
#include "Building.hpp"

class Asteroid
{
	private:
		Gosu::Graphics* graphics;

		const bool capturable;
		double x, y;

		vector<RessourceArea> ressourceAreas;
		vector<Building> building;

	public:
		Asteroid(Gosu::Graphics* graphics, bool capturable);
		

		void draw();
		void update();
};

#endif