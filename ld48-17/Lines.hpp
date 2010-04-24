#ifndef LINES_HPP
#define LINES_HPP

#include "Gosu.hpp"
#include "Buildings.hpp"

class Lines
{
	public:
		Gosu::Graphics* graphics;
		Building *start, *end;
		int type;

		Lines(Gosu::Graphics* graphics, int type)
			: graphics(graphics), type(type)
		{
			
		}

		void draw()
		{
			
		}

};

#endif