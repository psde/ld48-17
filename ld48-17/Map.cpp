#include "Map.hpp"


Map::Map(Gosu::Graphics* graphics)
: graphics(graphics), x(0), y(0)
{ 
	this->bg1 = new Gosu::Image(*graphics, L"data/bg1_c.png");

	for(int i = 0; i < 5; i++)
	{
		Asteroid* newAsteroid = new Asteroid(graphics, true);
		this->asteroids.push_back(newAsteroid);
	}
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

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != asteroids.end(); ++it)
	{
		(*it)->draw();
	}
}

void Map::update()
{
	this->x++;
	this->y++;
}