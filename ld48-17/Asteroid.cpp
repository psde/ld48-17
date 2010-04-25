#include "Asteroid.hpp"




Asteroid::Asteroid(Gosu::Graphics* graphics,  Gosu::Input* input, RessourceRenderer* resRenderer, bool capturable, double x, double y, int type, bool start)
: graphics(graphics), input(input), resRenderer(resRenderer), capturable(capturable), x(x), y(y), hover(0), maxHover(30), scouted(false)
{
	if(start) scouted = true;

	this->img = new Gosu::Image(*graphics, L"data/asteroids/" + boost::lexical_cast<std::wstring>(type) + L".png");
	this->w = this->img->width();
	this->h = this->img->height();
	
	this->imgBuildMap = new Gosu::Image(*graphics, L"data/asteroids/" + boost::lexical_cast<std::wstring>(type) + L".bmp");
	this->buildMap = Gosu::quickLoadBitmap(L"data/asteroids/" + boost::lexical_cast<std::wstring>(type) + L".bmp");


	int curRA = -1;

	wstring f = L"data/asteroids/" +  boost::lexical_cast<std::wstring>(type) + L".txt";
	char zeile[550];
	string szeile;

	std::ifstream eingabe(f.c_str(),ios::in);
	
	if (eingabe.good()) {
		eingabe.seekg(0L,ios::end);
		eingabe.seekg(0L,ios::beg);
		while (!eingabe.eof()) {
			eingabe.getline(zeile,500);
			szeile = zeile;
				
			if(szeile.find("=") < 99){
				string name = szeile.substr(0,1);
				string cmd = szeile.substr(0,szeile.find("="));
				string arg = szeile.substr(szeile.find("=")+1);

				if(cmd == "startDepot"){
					int dx = atoi(arg.substr(0,arg.find(",")).c_str());
					int dy = atoi(arg.substr(arg.find(",")+1,arg.find("@")).c_str());

					string res = arg.substr(arg.find("@")+1).c_str();

					int r1 = atoi(res.substr(0,res.find(",")).c_str());
					res = res.substr(res.find(",")+1).c_str();

					int r2 = atoi(res.substr(0,res.find(",")).c_str());
					res = res.substr(res.find(",")+1).c_str();

					int r3 = atoi(res.substr(0,res.find(",")).c_str());

					if(start)
					{
						Building* startDepot = new Building(dx, dy, Depot);
						startDepot->internalDepot[0] = r1;
						startDepot->internalDepot[1] = r2;
						startDepot->internalDepot[2] = r3;
						this->buildings.push_back(startDepot);
					}
				}
				
				if(cmd == "ressourceType"){
					//cout << arg << endl;
					RessourceArea* newRA = new RessourceArea(graphics);
					switch(atoi(arg.c_str()))
					{
						case 0:
							newRA->type = Ore;
							break;
						case 1:
							newRA->type = Silicon;
							break;
						case 2:
							newRA->type = Uranium;
							break;

					};
					curRA++;
					this->ressourceAreas.push_back(newRA);
				}

				if(cmd == "ressourceTons")
				{
					this->ressourceAreas[curRA]->availableTons = atoi(arg.c_str());
				}

				if(cmd == "ressourcePoint")
				{
					int dx = atoi(arg.substr(0,arg.find(",")).c_str());
					int dy = atoi(arg.substr(arg.find(",")+1,arg.find("@")).c_str());
					this->ressourceAreas[curRA]->area.push_back(Point2D(dx, dy));
				}


			}
		}
	}else{
		throw runtime_error("foo :(");
	}


	// Ressource-Area test:

	/*RessourceArea* testRA = new RessourceArea(graphics);
	testRA->availableTons = 100;
	testRA->type = Uranium;
	testRA->area.push_back(Point2D(226, 052));
	testRA->area.push_back(Point2D(311, 075));
	testRA->area.push_back(Point2D(357, 125));
	testRA->area.push_back(Point2D(371, 202));
	testRA->area.push_back(Point2D(317, 223));
	testRA->area.push_back(Point2D(237, 165));
	testRA->area.push_back(Point2D(178, 94));
	testRA->area.push_back(Point2D(226, 052));
	this->ressourceAreas.push_back(testRA);


	Building* test1 = new Building(100, 50, EnergyCollector);
	this->buildings.push_back(test1);

	RessourceArea* tmpRA = this->getRessourceAreaAt(270, 100);
	Building* test2 = new Building(270, 100, Mine, tmpRA);
	this->buildings.push_back(test2);

	Building* test3 = new Building(350, 250, Depot);
	this->buildings.push_back(test3);


	Line* newLine = new Line(graphics, resRenderer, 0);
	newLine->start = test1;
	newLine->end = test2;
	this->addLine(newLine);
	
	newLine = new Line(graphics, resRenderer, 1);
	newLine->start = test2;
	newLine->end = test3;
	this->addLine(newLine);*/

}

void Asteroid::draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY)
{
	this->img->draw(this->x - scrollX, this->y - scrollY, 10);
	//this->imgBuildMap->draw(this->x, this->y, 10); // Debug: Draw "hitmap" for buildable areas

	bool raHover = false;
	// Draw ressource areas
	for(vector<RessourceArea*>::iterator it = this->ressourceAreas.begin(); it != this->ressourceAreas.end(); ++it)
	{
		if(!scouted) break;

		RessourceArea* curRA = (*it);

		bool hovering = false;
		if(isInsideRessourceArea((int)input->mouseX()-this->x  + scrollX, (int)input->mouseY()-this->y  + scrollY, (*it)))
		{
			raHover = true;
			this->hover++;
			if(this->hover >= this->maxHover)
			{
				hovering = true;
			}
		}

		curRA->draw(this->x - scrollX, this->y - scrollY, hovering, (int)input->mouseX(), (int)input->mouseY(), this->resRenderer);
	}

	// Draw all lines
	for(vector<Line*>::iterator it = this->powerlines.begin(); it != this->powerlines.end(); ++it)
	{
		Line* curLine = (*it);

		curLine->draw(this->x - scrollX + 20, this->y - scrollY + 20);
	}	
	for(vector<Line*>::iterator it = this->transportlines.begin(); it != this->transportlines.end(); ++it)
	{
		Line* curLine = (*it);

		curLine->draw(this->x - scrollX + 20, this->y - scrollY + 20);
	}

	bool buildHover = false;
	// Draw all buildings
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);

		
		bool hovering = false;
		if(Gosu::distance(this->x + curBuild->x - scrollX + 20, this->y + curBuild->y - scrollY + 20, input->mouseX(), input->mouseY()) < 15) 
		{
			buildHover = true;
			this->hover++;
			if(this->hover >= this->maxHover)
			{
				hovering = true;
			}
		}


		buildRenderer.draw(curBuild, this->x + curBuild->x - scrollX, this->y + curBuild->y - scrollY, 12, hovering);

		/*this->buildingBackdrop->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 11);
		this->buildingEnergy->draw(this->x + curBuild.x - scrollX, this->y + curBuild.y - scrollY, 12);*/
	}

	if(raHover == false && buildHover == false)
	{
		this->hover = 0;
	}
	
}

void Asteroid::update()
{
	// Reset energy input
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		(*it)->energyIn = 0;
	}

	for(vector<Line*>::iterator it = this->powerlines.begin(); it != this->powerlines.end(); ++it)
	{
		(*it)->update();
	}

	for(vector<Line*>::iterator it = this->transportlines.begin(); it != this->transportlines.end(); ++it)
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
	if(x >= (int)this->buildMap.width() || y >= (int)this->buildMap.height()) return false;

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

bool Asteroid::isInsideRessourceArea(int x, int y, RessourceArea* curArea)
{
	for(int i = 0; i < curArea->area.size(); i++)
	{
		int fooLast = i-1;
		if(i == 0) fooLast = curArea->area.size()-1;
		Point2D last = curArea->area[fooLast];
		Point2D cur = curArea->area[i];

		double dx1 = x - last.x;
		double dy1 = y - last.y;

		double dx2 = cur.x - last.x;
		double dy2 = cur.y - last.y;

		if( (dx1*dy2) - (dx2 * dy1) > 0) 
		{
			return false;
		}
	}
	return true;
}

RessourceArea* Asteroid::getRessourceAreaAt(int x, int y)
{
	for(vector<RessourceArea*>::iterator it = this->ressourceAreas.begin(); it != this->ressourceAreas.end(); ++it)
	{
		RessourceArea* curArea = (*it);
		
		if(this->isInsideRessourceArea(x, y, curArea))
		{
			return (*it);
		}
	}
	return 0;
}

void Asteroid::placeBuilding(int x, int y, BuildingType type)
{
	if(this->isFree(x, y))
	{
		RessourceArea* tmpRA = this->getRessourceAreaAt(x, y);
		
		if(type == Mine && tmpRA == 0) return;


		int* buildingCosts = Building::getBuildingCost(type);
		if(!this->reduceRessources(buildingCosts[0], buildingCosts[1], buildingCosts[2])) return;

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
	if(l->type == 0)
	{
		this->powerlines.push_back(l);
	}
	else
	{
		this->transportlines.push_back(l);
	}
}

int* Asteroid::getRessources()
{
	int* foo = new int[3];
	foo[0] = 0;
	foo[1] = 0;
	foo[2] = 0;

	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);
		if(curBuild->type == Depot)
		{
			foo[0] += curBuild->internalDepot[0];
			foo[1] += curBuild->internalDepot[1];
			foo[2] += curBuild->internalDepot[2];
		}
	}

	return foo;
}

bool Asteroid::reduceRessources(int r1, int r2, int r3)
{
	int* res = this->getRessources();

	if(res[0] < r1 || res[1] < r2 || res[2] < r3)
	{
		return false;
	}

	int* foo = new int[3];
	foo[0] = r1;
	foo[1] = r2;
	foo[2] = r3;

	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);
		if(curBuild->type == Depot)
		{
			for(int i=0; i<3; i++)
			{
				if(foo[i] > 0)
				{
					if(curBuild->internalDepot[i] > foo[i])
					{
						curBuild->internalDepot[i] -= foo[i];
						foo[i] = 0;
					}
					else
					{
						int dif = foo[i] - curBuild->internalDepot[i];
						curBuild->internalDepot[i] = 0;
						foo[i] = dif;
					}
				}
			}
			
			//foo[0] += curBuild->internalDepot[0];
			//foo[1] += curBuild->internalDepot[1];
			//foo[2] += curBuild->internalDepot[2];
		}
	}

	return true;
}

Building* Asteroid::getDepot()
{
	for(vector<Building*>::iterator it = this->buildings.begin(); it != this->buildings.end(); ++it)
	{
		Building* curBuild = (*it);
		if(curBuild->type == Depot)
		{
			return (*it);
		}
	}
	return 0;
}