#include "Asteroid.hpp"


Asteroid::Asteroid(Gosu::Graphics* graphics, bool capturable, double x, double y, int type)
: graphics(graphics), capturable(capturable), x(x), y(y)
{
	this->img = new Gosu::Image(*graphics, L"data/asteroids/1.png");
	
	this->imgBuildMap = new Gosu::Image(*graphics, L"data/asteroids/1.bmp");
	this->buildMap = Gosu::quickLoadBitmap(L"data/asteroids/1.bmp");


	Building test(100, 50, EnergyCollector);
	this->buildings.push_back(test);



	// Ressource-Area test:

	RessourceArea testRA;
	testRA.availableTons = 100;
	testRA.type = 1;
	testRA.area.push_back(Point2D(326, 152));
	testRA.area.push_back(Point2D(411, 175));
	testRA.area.push_back(Point2D(457, 225));
	testRA.area.push_back(Point2D(471, 302));
	testRA.area.push_back(Point2D(417, 323));
	testRA.area.push_back(Point2D(337, 265));
	testRA.area.push_back(Point2D(278, 194));
	this->ressourceAreas.push_back(testRA);

			/*glVertex2f(326, 152);
		glVertex2f(411, 175);
		glVertex2f(457, 225);
		glVertex2f(471, 302);
		glVertex2f(417, 323);
		glVertex2f(337, 265);
		glVertex2f(278, 194);*/
}

void Asteroid::draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY)
{
	this->img->draw(this->x - scrollX, this->y - scrollY, 10);
	//this->imgBuildMap->draw(this->x, this->y, 10); // Debug: Draw "hitmap" for buildable areas

	// Draw ressource areas
	for(vector<RessourceArea>::iterator it = this->ressourceAreas.begin(); it != this->ressourceAreas.end(); ++it)
	{
		RessourceArea curRA = (*it);
		
		graphics->beginGL();

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		// TODO: color should fade to red
		glColor4f(0.20f, 0.3f, 0.11f, 0.7f);

		glBegin(GL_POLYGON);

		for(vector<Point2D>::iterator itp = curRA.area.begin(); itp != curRA.area.end(); ++itp)
		{
			Point2D curPoint = (*itp);
			glVertex2f(curPoint.x - scrollX, curPoint.y - scrollY);
		}

		glEnd();
	}

	// Draw all buildings
	for(vector<Building>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building curBuild = (*it);

		buildRenderer.draw(curBuild, this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 11);

		/*this->buildingBackdrop->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 11);
		this->buildingEnergy->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 12);*/
	}

	
}

void Asteroid::update()
{
	Gosu::Color test;
}

bool Asteroid::isFree(int x, int y)
{
	if(x < 0 || y < 0) return false;
	if(x > (int)this->buildMap.width() || y > (int)this->buildMap.height()) return false;

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

void Asteroid::placeBuilding(int x, int y, BuildingType type)
{
	if(this->isFree(x, y))
	{
		Building test(x, y, type);
		this->buildings.push_back(test);
	}
}