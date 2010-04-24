#include "Map.hpp"


Map::Map(Gosu::Graphics* graphics, double size)
: graphics(graphics), x(0), y(0), size(size)
{ 
	this->bg1 = new Gosu::Image(*graphics, L"data/bg1_c.png");


};

void Map::draw()
{
	// Black space background
	this->graphics->drawQuad(0, 0, Gosu::Colors::black,
							 0, graphics->width(), Gosu::Colors::black,
							 graphics->height(), 0, Gosu::Colors::black, 
							 graphics->height(), graphics->width(), Gosu::Colors::black, 
							 0);

	for(int x = 0; x < 3; x++)
	{
		for(int y = 0; y < 2; y++)
		{
			this->bg1->draw((x * 500), (y * 500), 1);
		}
	}
}

void Map::update()
{

}