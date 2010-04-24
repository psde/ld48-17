#ifndef MAP_HPP
#define MAP_HPP

#include "Gosu.hpp"

class Map
{
	private:
		Gosu::Graphics* graphics;

		Gosu::Image* bg1;

	public:
		double x, y, size;

		Map(Gosu::Graphics* graphics, double size);

		void update();
		void draw();
		void buttonDown(Gosu::Button button);

};

#endif