#ifndef MAP_HPP
#define MAP_HPP

#include "Gosu.hpp"
#include "Asteroid.hpp"

class Map
{
	private:
		Gosu::Graphics* graphics;

		Gosu::Image* bg1;

		double x, y;

		vector<Asteroid*> asteroids;

	public:

		Map(Gosu::Graphics* graphics);

		void update();
		void draw();
		void buttonDown(Gosu::Button button);

};

#endif