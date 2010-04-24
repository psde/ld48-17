#include "Asteroid.hpp"


Asteroid::Asteroid(Gosu::Graphics* graphics, Gosu::Input* input, bool capturable, double x, double y, int type)
: graphics(graphics), input(input), capturable(capturable), x(x), y(y)
{
	this->img = new Gosu::Image(*graphics, L"data/asteroids/1.png");
	
	this->imgBuildMap = new Gosu::Image(*graphics, L"data/asteroids/1.bmp");
	this->buildMap = Gosu::quickLoadBitmap(L"data/asteroids/1.bmp");

	/*Building test(100, 50, EnergyCollector);
	this->buildings.push_back(test);*/

	// Ressource-Area test:

	RessourceArea* testRA = new RessourceArea(graphics);
	testRA->availableTons = 100;
	testRA->type = Uranium;
	testRA->area.push_back(Point2D(226, 052));
	testRA->area.push_back(Point2D(311, 075));
	testRA->area.push_back(Point2D(357, 125));
	testRA->area.push_back(Point2D(371, 202));
	testRA->area.push_back(Point2D(317, 223));
	testRA->area.push_back(Point2D(237, 165));
	testRA->area.push_back(Point2D(178, 94));
	this->ressourceAreas.push_back(testRA);

}

void Asteroid::draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY)
{
	this->img->draw(this->x - scrollX, this->y - scrollY, 10);
	//this->imgBuildMap->draw(this->x, this->y, 10); // Debug: Draw "hitmap" for buildable areas

	// Draw ressource areas
	for(vector<RessourceArea*>::iterator it = this->ressourceAreas.begin(); it != this->ressourceAreas.end(); ++it)
	{
		RessourceArea* curRA = (*it);

		curRA->draw(this->x - scrollX, this->y - scrollY);
	}

	// Draw all lines
	for(vector<Line*>::iterator it = this->lines.begin(); it != this->lines.end(); ++it)
	{
		Line* curLine = (*it);

		curLine->draw(this->x - scrollX + 20, this->y - scrollY + 20);
	}

	// Draw all buildings
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);

		bool hover = false;
		if(Gosu::distance(this->x + curBuild->x - scrollX + 20, this->y + curBuild->y - scrollY + 20, input->mouseX(), input->mouseY()) < 15) 
		{
			hover = true;
		}

		buildRenderer.draw(curBuild, this->x + curBuild->x - scrollX, this->y + curBuild->y - scrollY, 12, hover);

		/*this->buildingBackdrop->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 11);
		this->buildingEnergy->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 12);*/
	}

	
}

void Asteroid::update()
{
	// Reset energy input
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		(*it)->energyIn = 0;
	}

	for(vector<Line*>::iterator it = this->lines.begin(); it != this->lines.end(); ++it)
	{
		(*it)->update();
	}

	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		(*it)->update();
	}

}

bool Asteroid::isFree(int x, int y)
{
	if(x < 0 || y < 0) return false;
	if(x > (int)this->buildMap.width() || y > (int)this->buildMap.height()) return false;

	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);

		if(Gosu::distance(curBuild->x, curBuild->y, x, y) < 42) return false;
	}

	if(this->buildMap.getPixel(x, y).red() == 255)
		return true;
	else
		return false;
}

RessourceArea* Asteroid::getRessourceAreaAt(int x, int y)
{
	return this->ressourceAreas[0];
}

void Asteroid::placeBuilding(int x, int y, BuildingType type)
{
	if(this->isFree(x, y))
	{
		RessourceArea* tmpRA = this->getRessourceAreaAt(x, y);
		
		if(type == Mine && tmpRA == 0) return;

		Building* test = new Building(x, y, type, tmpRA);
		this->buildings.push_back(test);
	}
}

Building* Asteroid::getBuildingAt(int x, int y, int scrollX, int scrollY)
{
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);
		if(Gosu::distance(this->x + curBuild->x - scrollX + 20, this->y + curBuild->y - scrollY + 20, x, y) < 15) 
		{
			return curBuild;
		}
	}
	return 0;
}

void Asteroid::addLine(Line *l)
{
	this->lines.push_back(l);
}