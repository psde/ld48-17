#include "Asteroid.hpp"


Asteroid::Asteroid(Gosu::Graphics* graphics, bool capturable, double x, double y, int type)
: graphics(graphics), capturable(capturable), x(x), y(y)
{
	this->img = new Gosu::Image(*graphics, L"data/asteroids/1.png");
	
	this->imgBuildMap = new Gosu::Image(*graphics, L"data/asteroids/1.bmp");
	this->buildMap = Gosu::quickLoadBitmap(L"data/asteroids/1.bmp");


	Building test(100, 50);
	this->buildings.push_back(test);

	this->buildingBackdrop = new Gosu::Image(*graphics, L"data/buildings/backdrop.png");
	this->buildingEnergy = new Gosu::Image(*graphics, L"data/buildings/energy.png");
}

void Asteroid::draw()
{
	this->img->draw(this->x, this->y, 10);
	//this->imgBuildMap->draw(this->x, this->y, 10);


	for(vector<Building>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building curBuild = (*it);

		this->buildingBackdrop->draw(this->x + curBuild.x, this->y + curBuild.y, 11);
		this->buildingEnergy->draw(this->x + curBuild.x, this->y + curBuild.y, 12);
	}
}

void Asteroid::update()
{
	Gosu::Color test;
}

bool Asteroid::isFree(int x, int y)
{
	if(x < 0 || y < 0) return false;
	if(x > this->buildMap.width() || y > this->buildMap.height()) return false;

	for(vector<Building>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building curBuild = (*it);

		if(Gosu::distance(curBuild.x, curBuild.y, x, y) < 42) return false;
	}

	if(this->buildMap.getPixel(x, y).red() == 255)
		return true;
	else
		return false;
}

void Asteroid::placeBuilding(int x, int y)
{
	if(this->isFree(x, y))
	{
		Building test(x, y);
		this->buildings.push_back(test);
	}
}