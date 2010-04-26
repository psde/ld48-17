#include "Game.hpp"

Game::Game(Gosu::Graphics* graphics, Gosu::Input* input)
: graphics(graphics), input(input), selectStart(0, 0), selecting(false), cargoStep(1), factory(0)
{

	this->cursor = new Gosu::Image(*graphics, L"data/cursor.png");
	this->cursor_move = new Gosu::Image(*graphics, L"data/cursor_move.png");
	this->cursor_special = new Gosu::Image(*graphics, L"data/cursor_special.png");
	this->cursor_up = new Gosu::Image(*graphics, L"data/up.png");
	this->cursor_down = new Gosu::Image(*graphics, L"data/down.png");

	this->buildRenderer = new BuildingRenderer(graphics);
	this->resRenderer = new RessourceRenderer(graphics);
	this->unitRenderer = new UnitRenderer(graphics);
	this->lineStart = 0;

	this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 14);
	this->bigFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 22);

	/*for(int i = 0; i < 1; i++)
	{
		Asteroid* newAsteroid = new Asteroid(graphics, input, true, 100, 100, 1);
		this->asteroids.push_back(newAsteroid);
	}*/

	Asteroid* newAsteroid1 = new Asteroid(graphics, input, resRenderer, true, 500, 300, 1, true);
	this->asteroids.push_back(newAsteroid1);

	Asteroid* newAsteroid2 = new Asteroid(graphics, input, resRenderer, true, 700, 850, 2);
	this->asteroids.push_back(newAsteroid2);

	Asteroid* newAsteroid3 = new Asteroid(graphics, input, resRenderer, true, 2700, 1250, 3);
	this->asteroids.push_back(newAsteroid3);

	Asteroid* newAsteroid4 = new Asteroid(graphics, input, resRenderer, true, 100, 1450, 4);
	this->asteroids.push_back(newAsteroid4);

	Asteroid* newAsteroid5 = new Asteroid(graphics, input, resRenderer, true, 300, 2500, 1);
	this->asteroids.push_back(newAsteroid5);

	Asteroid* newAsteroid6 = new Asteroid(graphics, input, resRenderer, true, 900, 3050, 4);
	this->asteroids.push_back(newAsteroid6);

	this->gamemap = new Map(graphics, 5000);
	this->gamemap->x = 200;
	this->gamemap->y = 200;
	this->playState = Normal;
	this->activeAsteroid = 0;

	/*Unit* testUnit1 = new Unit(200, 200, Cargo);
	this->units.push_back(testUnit1);

	Unit* testUnit2 = new Unit(250, 200, Scout);
	this->units.push_back(testUnit2);

	Unit* testUnit3 = new Unit(600, 500, Colo);
	this->units.push_back(testUnit3);

	this->selectedUnits.push_back(testUnit3);

	this->playState = FactoryGUI;
	this->factory = this->asteroids[0]->buildings[1];*/


}

bool Game::isUnitSelected(Unit* unit)
{
	for(vector<Unit*>::iterator it = this->selectedUnits.begin(); it != this->selectedUnits.end(); ++it)
	{
		Unit* curUnit = (*it);
		if(curUnit == unit) return true;
	}
	return false;
}

void Game::draw()
{
	this->gamemap->draw();

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->draw(*this->buildRenderer, (int)gamemap->x, (int)gamemap->y);
	}

	for(vector<Unit*>::iterator it = this->units.begin(); it != this->units.end(); ++it)
	{
		Unit* curUnit = (*it);
		this->unitRenderer->drawUnit(curUnit->x - gamemap->x, curUnit->y - gamemap->y, 50, curUnit, isUnitSelected(curUnit), gamemap->x, gamemap->y);
	}

	this->smallFont->draw(L"mx: " +  boost::lexical_cast<std::wstring>(input->mouseX()), 10, 10, 9999);
	this->smallFont->draw(L"my: " +  boost::lexical_cast<std::wstring>(input->mouseY()), 10, 20, 9999);

	this->smallFont->draw(L"x: " +  boost::lexical_cast<std::wstring>(gamemap->x), 10, 40, 9999);
	this->smallFont->draw(L"y: " +  boost::lexical_cast<std::wstring>(gamemap->y), 10, 50, 9999);

	bool testFree = this->asteroids[activeAsteroid]->isFree((int)input->mouseX()-120, (int)input->mouseY()-120);
	this->smallFont->draw(L"free? " +  boost::lexical_cast<std::wstring>(testFree), 10, 60, 9999);

	
	RessourceArea* testArea = this->asteroids[activeAsteroid]->getRessourceAreaAt((int)input->mouseX()-100, (int)input->mouseY()-100);
	int testAreaType = -1;
	if(testArea != 0) testAreaType = testArea->type;
	this->smallFont->draw(L"free? " +  boost::lexical_cast<std::wstring>(testAreaType), 10, 70, 9999);


	this->smallFont->draw(L"active asteroid " +  boost::lexical_cast<std::wstring>(this->activeAsteroid), 10, 80, 9999);



	// GUI:
	Gosu::Color guiBackground(240, 50, 50, 50);
	Gosu::Color guiBackgroundFade(130, 50, 50, 50);
	graphics->drawQuad(250, 0, guiBackground, 774, 0, guiBackground, 250, 70, guiBackgroundFade, 774, 70, guiBackgroundFade, 1000);
	
	this->cursor->draw(320, 20, 1001);
	graphics->drawLine(360, 20, Gosu::Colors::aqua, 380, 40, Gosu::Colors::aqua, 1001);
	graphics->drawLine(410, 20, Gosu::Colors::red, 430, 40, Gosu::Colors::red, 1001);
	this->buildRenderer->drawProp(Building(0, 0, EnergyCollector), 450, 10, 1001);
	this->buildRenderer->drawProp(Building(0, 0, Mine), 500, 10, 1001);
	//this->buildRenderer->drawProp(Building(0, 0, Depot), 550, 10, 1001);
	this->buildRenderer->drawProp(Building(0, 0, Factory), 550, 10, 1001);
	this->buildRenderer->drawProp(Building(0, 0, Spaceport), 600, 10, 1001);

	int* res = this->asteroids[activeAsteroid]->getRessources();
	this->resRenderer->draw(400, 50, 1001, Ore);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[0]), 427, 53, 1001);

	this->resRenderer->draw(500, 50, 1001, Silicon);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[1]), 527, 53, 1001);

	this->resRenderer->draw(600, 50, 1001, Uranium);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[2]), 627, 53, 1001);
	
	// Ship-GUI:


	if(this->selectedUnits.size() == 1)
	{
		graphics->drawQuad(250, 700, guiBackgroundFade, 774, 700, guiBackgroundFade, 250, 768, guiBackground, 774, 768, guiBackground, 1000);

		switch(this->selectedUnits[0]->type)
		{
			case Scout:
				this->smallFont->draw(L"Scout", 260, 710, 1001);
				break;

			case Colo:
				this->smallFont->draw(L"Colonization", 260, 710, 1001);
				break;

			case Cargo:
				this->smallFont->draw(L"Cargoship", 260, 710, 1001);
				break;
		}


		this->cursor_special->draw(290, 725, 1001);

		int nearAsteroid = this->getNearAsteroid(this->selectedUnits[0]);
		
		
		if(nearAsteroid != -1)
		{
			Building* depot = this->asteroids[nearAsteroid]->getDepot();
			for(int i=0;i<3;i++)
			{
				if(depot != 0)
				{
					this->smallFont->draw(L"" + boost::lexical_cast<std::wstring>(depot->internalDepot[i]) + L"t", 345 + i*60, 710, 1001);

					this->cursor_up->draw(375 + i*60, 720, 1001);
					if(this->asteroids[nearAsteroid]->hasSpaceport())
					{	
						this->cursor_down->draw(375 + i*60, 740, 1001);
					}
				}

				this->resRenderer->draw(340 + i*60, 720, 1001, Ressource::getType(i), 1.5);
				this->smallFont->draw(L"" + boost::lexical_cast<std::wstring>(this->selectedUnits[0]->cargo[i]) + L"t", 345 + i*60, 750, 1001);
			}
			
			if(depot == 0)
			{
				this->smallFont->draw(L"No Headquarter on asteroid!", 340, 710, 1001, 1, 1, Gosu::Colors::red);
			}else if(!this->asteroids[nearAsteroid]->hasSpaceport())
			{	
				this->smallFont->draw(L"No Spaceport on asteroid!", 530, 750, 1001, 1, 1, Gosu::Colors::red);
			}

			this->smallFont->draw(L"Steps: ", 530, 710, 1001);
			this->smallFont->draw(L"1t", 570, 710, 1001, 1, 1, (this->cargoStep == 1 ? Gosu::Colors::aqua : Gosu::Colors::white));
			this->smallFont->draw(L"10t", 585, 710, 1001, 1, 1, (this->cargoStep == 10 ? Gosu::Colors::aqua : Gosu::Colors::white));
			this->smallFont->draw(L"100t", 605, 710, 1001, 1, 1, (this->cargoStep == 100 ? Gosu::Colors::aqua : Gosu::Colors::white));
		}
		else
		{
			for(int i=0;i<3;i++)
			{
				this->resRenderer->draw(340 + i*60, 720, 1001, Ressource::getType(i), 1.5);
				this->smallFont->draw(L"" + boost::lexical_cast<std::wstring>(this->selectedUnits[0]->cargo[i]) + L"t", 345 + i*60, 750, 1001);
			}
		}

		this->smallFont->draw(L"Capacity left: " + boost::lexical_cast<std::wstring>(this->selectedUnits[0]->getCapacityLeft()) + L"t", 530, 730, 1001);
	}


	// Factory GUI:

	if(this->playState == FactoryGUI && this->factory != 0)
	{
		graphics->drawQuad(250, 315, guiBackgroundFade, 774, 315, guiBackgroundFade, 250, 440, guiBackground, 774, 440, guiBackground, 1000);


		for(int i = 0; i < 3; i ++)
		{	
			switch(i)
			{
				case 0:
					this->bigFont->draw(L"Scout", 285 + i*160, 320, 1001);
					break;

				case 1:
					this->bigFont->draw(L"Colonization", 285 + i*150, 320, 1001);
					break;

				case 2:
					this->bigFont->draw(L"Cargoship", 285 + i*140, 320, 1001);
					break;
			}

			this->unitRenderer->drawUnitProp(270 + i*160, 345, 1002, Unit::getUnitType(i), 2);

			int* costs = Unit::getUnitCosts(Unit::getUnitType(i));
			for(int r = 0; r < 3; r++)
			{
				this->resRenderer->draw(360 + i*160, 350 + r*20, 1001, Ressource::getType(r), 1.1);
				this->smallFont->draw(L"" + boost::lexical_cast<std::wstring>(costs[r]), 395 + i*160, 353 + r*20, 1001);
			}
			
			this->smallFont->draw(L"Buildtime:" + boost::lexical_cast<std::wstring>(Unit::getUnitBuildTime(Unit::getUnitType(i))), 355 + i*160, 353 + 3*20, 1001);
		}
		
	}


/*
	GosuEx::Shader local(*graphics);
	static GosuEx::ShaderProgram program = local.compile(L"data/shader/ressourceArea.frag");
*/

	if(this->playState == PlaceEnergyline || this->playState == PlaceTransportline)
	{
		if(this->lineStart != 0)
		{
			Gosu::Color c1 = Gosu::Colors::red;
			if(this->playState == PlaceTransportline) c1 = Gosu::Colors::aqua;
			Gosu::Color c2 = c1;
			c2.setAlpha(120);

			graphics->drawLine(this->lineStart->x - this->gamemap->x + this->asteroids[activeAsteroid]->x + 20, this->lineStart->y - this->gamemap->y + this->asteroids[activeAsteroid]->y + 20, c2, (int)input->mouseX(), (int)input->mouseY(), c1, 11);	
		}
	}

	// Draw the cursor
	if(this->playState == ShipSpecial)
	{
		this->cursor_special->draw((int)input->mouseX(), (int)input->mouseY(), 9999);
	}
	else
	{
		this->cursor->draw((int)input->mouseX(), (int)input->mouseY(), 9999);
		if(this->playState == PlaceBuilding)
		{
			this->buildRenderer->drawProp(Building(0, 0, this->placingBuilding), (int)input->mouseX() - 20, (int)input->mouseY() - 20, 9995);
		}
	}

	if(this->playState == Normal && this->selecting)
	{
		Gosu::Color c(120, 255, 255, 255);
		graphics->drawQuad(this->selectStart.x - gamemap->x, this->selectStart.y - gamemap->y, c, (int)input->mouseX(), this->selectStart.y - gamemap->y, c,
						   this->selectStart.x - gamemap->x, (int)input->mouseY(), c, (int)input->mouseX(), (int)input->mouseY(), c, 9998); 
	}



	// draw some help for the player if inside the top gui
	int x = (int)input->mouseX();
	int y = (int)input->mouseY();

	if(x > 250 && x < 774 && y > 0 && y < 70)
	{	
		int selection = -1;
		for(int i = 0; i < 7; i++)
		{
			if(Gosu::distance(x, y, 325 + i*50, 25) < 30)
			{
				selection = i;
				break;
			}
		}
		
		int length=-1;
		int height=25;
		int* cost = 0;

		switch(selection)
		{
			case 0:
				this->smallFont->draw(L"Selection mode", x+5, y+35, 5001);
				length = 100;
				break;

			case 1:
				this->smallFont->draw(L"Place Transportline", x+5, y+35, 5001);
				length = 120;
				break;

			case 2:
				this->smallFont->draw(L"Place Powerline", x+5, y+35, 5001);
				length = 100;
				break;

			case 3:
				this->smallFont->draw(L"Build Energy collector", x+5, y+35, 5001);
				
				cost = Building::getBuildingCost(EnergyCollector);
				this->resRenderer->draw(x+5, y+50, 5001, Ore);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[0]), x+30, y+53, 5001);

				this->resRenderer->draw(x+50, y+50, 5001, Silicon);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[1]), x+75, y+53, 5001);

				this->resRenderer->draw(x+95, y+50, 5001, Uranium);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[2]), x+120, y+53, 5001);

				height = 40;
				length = 150;
				break;

			case 4:
				this->smallFont->draw(L"Build Harvester", x+5, y+35, 5001);
				
				cost = Building::getBuildingCost(Mine);
				this->resRenderer->draw(x+5, y+50, 5001, Ore);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[0]), x+30, y+53, 5001);

				this->resRenderer->draw(x+50, y+50, 5001, Silicon);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[1]), x+75, y+53, 5001);

				this->resRenderer->draw(x+95, y+50, 5001, Uranium);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[2]), x+120, y+53, 5001);

				height = 40;
				length = 150;
				break;

			/*case 5:
				this->smallFont->draw(L"Build Cargodepot", x+5, y+35, 5001);
				
				cost = Building::getBuildingCost(Depot);
				this->resRenderer->draw(x+5, y+50, 5001, Ore);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[0]), x+30, y+53, 5001);

				this->resRenderer->draw(x+50, y+50, 5001, Silicon);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[1]), x+75, y+53, 5001);

				this->resRenderer->draw(x+95, y+50, 5001, Uranium);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[2]), x+120, y+53, 5001);

				height = 40;
				length = 150;
				break;*/

			case 5:
				this->smallFont->draw(L"Build Factory", x+5, y+35, 5001);
				
				cost = Building::getBuildingCost(Factory);
				this->resRenderer->draw(x+5, y+50, 5001, Ore);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[0]), x+30, y+53, 5001);

				this->resRenderer->draw(x+50, y+50, 5001, Silicon);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[1]), x+75, y+53, 5001);

				this->resRenderer->draw(x+95, y+50, 5001, Uranium);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[2]), x+120, y+53, 5001);

				height = 40;
				length = 150;
				break;

			case 6:
				this->smallFont->draw(L"Build Spaceport", x+5, y+35, 5001);
				
				cost = Building::getBuildingCost(Spaceport);
				this->resRenderer->draw(x+5, y+50, 5001, Ore);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[0]), x+30, y+53, 5001);

				this->resRenderer->draw(x+50, y+50, 5001, Silicon);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[1]), x+75, y+53, 5001);

				this->resRenderer->draw(x+95, y+50, 5001, Uranium);
				this->smallFont->draw(L""+boost::lexical_cast<std::wstring>(cost[2]), x+120, y+53, 5001);

				height = 40;
				length = 150;
				break;
		}

		if(length != -1) 
			graphics->drawQuad(x, y+30, guiBackground, x+length, y+30, guiBackground, x, y+30+height, guiBackgroundFade, x+length, y+30+height, guiBackgroundFade, 5000);

	}

	// same for bottom gui

}

void Game::update()
{
	this->gamemap->update();

	for(int i = 0; i < this->asteroids.size(); i++)
	{
		this->asteroids[i]->update(this->units, this->gamemap->x, this->gamemap->y);

		// check which asteroid

		
		int mX = (int)input->mouseX() + this->gamemap->x;
		int mY = (int)input->mouseY() + this->gamemap->y;
		if(mX > this->asteroids[i]->x && mX < this->asteroids[i]->w+this->asteroids[i]->x &&
		   mY > this->asteroids[i]->y && mY < this->asteroids[i]->h+this->asteroids[i]->y)
		{
			activeAsteroid = i;
		}
	}

	for(vector<Unit*>::iterator it = this->units.begin(); it != this->units.end(); )
	{
		bool del = false;

		Unit* curUnit = (*it);
		UnitUpdateResult foo = curUnit->update();

		if(foo != NothingSpecial)
		{
			// Which asteroid?
			int roid = -1;
			for(int i = 0; i < this->asteroids.size(); i++)
			{
				int mX = curUnit->x;
				int mY = curUnit->y;
				if(mX > this->asteroids[i]->x && mX < this->asteroids[i]->w+this->asteroids[i]->x &&
				   mY > this->asteroids[i]->y && mY < this->asteroids[i]->h+this->asteroids[i]->y)
				{
					roid = i;
				}
			}
			if(roid != -1)
			{
				if(foo == AsteroidScouted)
				{
					this->asteroids[roid]->scouted = true;
				}
				if(foo == AsteroidColonizized)
				{
					if(this->asteroids[roid]->colonize())
					{

						Building* depot = this->asteroids[roid]->getDepot();
						depot->internalDepot[0] = curUnit->cargo[0];
						depot->internalDepot[1] = curUnit->cargo[1];
						depot->internalDepot[2] = curUnit->cargo[2];

						del = true;
						this->selectedUnits.clear();
						this->playState = Normal;
					}
				}
			}
		}
		if(del)
		{
			it = this->units.erase(it);
		}
		else
		{
			it++;
		}
	}

	if(input->down(Gosu::kbLeft)) gamemap->x -= 10;
	if(input->down(Gosu::kbRight)) gamemap->x += 10;
	if(input->down(Gosu::kbUp)) gamemap->y -= 10;
	if(input->down(Gosu::kbDown)) gamemap->y += 10;

	if(gamemap->x < 0) gamemap->x = 0;
	if(gamemap->y < 0) gamemap->y = 0;
	if(gamemap->x > gamemap->size) gamemap->x = gamemap->size;
	if(gamemap->y > gamemap->size) gamemap->y = gamemap->size;


	int x = (int)input->mouseX();
	int y = (int)input->mouseY();

	if(x > 950) this->gamemap->x+=5;
	if(x > 1000) this->gamemap->x+=7;
	if(x < 140) this->gamemap->x-=5;
	if(x < 70) this->gamemap->x-=7;


	if(y > 690) this->gamemap->y+=5;
	if(y > 750) this->gamemap->y+=7;

	if(!(x > 250 && x < 774 && y > 0 && y < 141))
	{
		if(y < 140) this->gamemap->y-=5;
		if(y < 70) this->gamemap->y-=7;
	}

}

void Game::buttonDown(Gosu::Button button)
{
	if(button == Gosu::msRight)
	{
		this->playState = Normal;
		this->selecting = false;
		this->selectedUnits.clear();
	}

	if(button == Gosu::msLeft)
	{
		// check if inside of gui
		int x = (int)input->mouseX();
		int y = (int)input->mouseY();

		if(x > 250 && x < 774 && y > 0 && y < 70)
		{	
			int selection = -1;
			for(int i = 0; i < 7; i++)
			{
				if(Gosu::distance(x, y, 325 + i*50, 25) < 30)
				{
					selection = i;
					break;
				}
			}

			if(selection >=1) this->selectedUnits.clear();

			switch(selection)
			{
				case -1:
					break;

				case 0:
					this->playState = Normal;
					break;

				case 1:
					this->playState = PlaceTransportline;
					this->lineStart = 0;
					break;

				case 2:
					this->playState = PlaceEnergyline;
					this->lineStart = 0;
					break;

				case 3:
					this->playState = PlaceBuilding;
					this->placingBuilding = EnergyCollector;
					break;

				case 4:
					this->playState = PlaceBuilding;
					this->placingBuilding = Mine;
					break;

				/*case 5:
					this->playState = PlaceBuilding;
					this->placingBuilding = Depot;
					break;*/

				case 5:
					this->playState = PlaceBuilding;
					this->placingBuilding = Factory;
					break;

				case 6:
					this->playState = PlaceBuilding;
					this->placingBuilding = Spaceport;
					break;
			};
		}
		else if(this->selectedUnits.size() == 1 && x > 250 && x < 774 && y > 700 && y < 774)
		{
			
			if(x > 280 && x < 350 && y > 705 && y < 760)
			{
				this->playState = ShipSpecial;	
				return;
			}


			int nearAsteroid = this->getNearAsteroid(this->selectedUnits[0]);
			if(nearAsteroid == -1) return;

			for(int i = 0; i < 3; i++)
			{
				if(Gosu::distance(x, y, 375 + i*60, 725) < 20) // up
				{
					if(this->selectedUnits[0]->cargo[i] == 0) return;

					int min = this->cargoStep;
					if(min > this->selectedUnits[0]->cargo[i]) min = this->selectedUnits[0]->cargo[i];
					//if(min > this->asteroids[nearAsteroid]->getDepot()->internalDepot[i]) min = this->asteroids[nearAsteroid]->getDepot()->internalDepot[i];
					


					this->asteroids[nearAsteroid]->getDepot()->internalDepot[i]+=min;
					this->selectedUnits[0]->cargo[i]-=min;
					break;
				}				
				if(Gosu::distance(x, y, 375 + i*60, 740) < 20) // down
				{
					if(this->asteroids[nearAsteroid]->getDepot()->internalDepot[i] == 0) return;
					if(!this->asteroids[nearAsteroid]->hasSpaceport()) return;

					int min = this->cargoStep;
					if(min > this->selectedUnits[0]->getCapacityLeft()) min = this->selectedUnits[0]->getCapacityLeft();
					if(min > this->asteroids[nearAsteroid]->getDepot()->internalDepot[i]) min = this->asteroids[nearAsteroid]->getDepot()->internalDepot[i];

					if(min < 0) return;

					this->asteroids[nearAsteroid]->getDepot()->internalDepot[i]-=min;
					this->selectedUnits[0]->cargo[i]+=min;

					break;
				}

				if(x > 570 && x < 585 && y > 710 && y < 720) this->cargoStep = 1;
				if(x > 585 && x < 605 && y > 710 && y < 720) this->cargoStep = 10;
				if(x > 605 && x < 635 && y > 710 && y < 720) this->cargoStep = 100;
			}
		}
		else if(this->playState == FactoryGUI)
		{
			for(int i = 0; i < 3; i++)
			{
				if(x > 270+i*160 && x < 270+140+i*160 && y > 345 && y < 500)
				{
					this->factory->unitInBuild = Unit::getUnitType(i);
					this->factory->wantsRes[0] = Unit::getUnitCosts(Unit::getUnitType(i))[0];
					this->factory->wantsRes[1] = Unit::getUnitCosts(Unit::getUnitType(i))[1];
					this->factory->wantsRes[2] = Unit::getUnitCosts(Unit::getUnitType(i))[2];
					
					this->playState = Normal;
					return;
				}
			}
		}
		else
		{

			if(this->playState == Normal)
			{
				if(this->selectedUnits.size() > 0)
				{
					// order units arround!
					int mod = 42;
					for(int i = 0; i < this->selectedUnits.size(); i++)
					{						
						selectedUnits[i]->order = DoMove;
						selectedUnits[i]->targetX = (int)input->mouseX() + this->gamemap->x-20 + mod*i;
						selectedUnits[i]->targetY = (int)input->mouseY() + this->gamemap->y-20 + (mod%(i+1))*mod;
					}
				}
				else
				{
					this->selectedUnits.clear();
					this->selecting = true;
					this->selectStart = Point2D((int)input->mouseX() + this->gamemap->x, (int)input->mouseY() + this->gamemap->y);

					Building* clickedBuilding = this->asteroids[activeAsteroid]->getBuildingAt((int)input->mouseX(), (int)input->mouseY(), this->gamemap->x, this->gamemap->y);
					if(clickedBuilding != 0)
					{
						if(clickedBuilding->type == Factory)
						{
							this->factory = clickedBuilding;
							this->playState = FactoryGUI;
							this->selecting = false;
							return;
						}
					}
				}
			}else{
				this->selecting = false;
			}
			
			if(this->playState == PlaceBuilding)
			{
				this->asteroids[activeAsteroid]->placeBuilding((int)input->mouseX()-this->asteroids[activeAsteroid]->x - 20 + this->gamemap->x, (int)input->mouseY()-this->asteroids[activeAsteroid]->y - 20 + this->gamemap->y, this->placingBuilding);
			}

			if(this->playState == PlaceEnergyline || this->playState == PlaceTransportline)
			{
				Building* clickedBuilding = this->asteroids[activeAsteroid]->getBuildingAt((int)input->mouseX(), (int)input->mouseY(), this->gamemap->x, this->gamemap->y);
				if(clickedBuilding != 0)
				{
					if(this->lineStart == 0)
					{
						if(clickedBuilding->type == EnergyCollector || (this->playState == PlaceTransportline && clickedBuilding->type != EnergyCollector) )
						{
							lineStart = clickedBuilding;
						}
					}
					else
					{
						if(clickedBuilding->type == EnergyCollector) return;

						Line* newLine = new Line(graphics, resRenderer, (this->playState == PlaceEnergyline ? 0 : 1));
						newLine->start = lineStart;
						newLine->end = clickedBuilding;

						if(this->playState == PlaceTransportline)
						{
							if((newLine->start->type == Depot && newLine->end->type == Mine) || (newLine->start->type == Factory && newLine->end->type == Depot))
							{
								Building *tmp = newLine->start;
								newLine->start = newLine->end;
								newLine->end = tmp;
							};

						}

						this->asteroids[activeAsteroid]->addLine(newLine);
						lineStart = 0;
					}
				}
			}

			if(this->playState == ShipSpecial)
			{
				if(this->selectedUnits.size() != 1) return;
				if(this->selectedUnits[0]->type == Cargo) return;

				// check if user clicked asteroid
				int roid = -1;
				for(int i = 0; i < this->asteroids.size(); i++)
				{
					int mX = (int)input->mouseX() + this->gamemap->x;
					int mY = (int)input->mouseY() + this->gamemap->y;
					if(mX > this->asteroids[i]->x && mX < this->asteroids[i]->w+this->asteroids[i]->x &&
					   mY > this->asteroids[i]->y && mY < this->asteroids[i]->h+this->asteroids[i]->y)
					{
						roid = i;
					}
				}

				if(roid != -1)
				{
					this->selectedUnits[0]->targetX = this->asteroids[roid]->x + this->asteroids[roid]->w/2;
					this->selectedUnits[0]->targetY = this->asteroids[roid]->y + this->asteroids[roid]->h/2;
					this->selectedUnits[0]->order = DoSpecial;
					this->playState = Normal;
				}

			}

		}
	}
}

void Game::buttonUp(Gosu::Button button)
{
	if(button == Gosu::msLeft)
	{
		if(this->playState == Normal && this->selecting)
		{
			
			this->selecting = false;


			//check distance, if we only clicked once, only select ONE unit!
			int sX = this->selectStart.x;
			int sY = this->selectStart.y;
			int eX = gamemap->x + (int)input->mouseX();
			int eY = gamemap->y + (int)input->mouseY();

			if(Gosu::distance(sX, sY, eX, eY) < 20)
			{
				this->selectedUnits.clear();

				for(vector<Unit*>::iterator it = this->units.begin(); it != this->units.end(); ++it)
				{
					Unit* curUnit = (*it);
					if(Gosu::distance(sX-20, sY-20, curUnit->x, curUnit->y) < 17)
					{
						this->selectedUnits.push_back((*it));
					}

				}
				return;
			}

			if(sX > eX)
			{
				int tmp = sX;
				sX = eX;
				eX = tmp;
			}

			if(sY > eY)
			{
				int tmp = sY;
				sY = eY;
				eY = tmp;
			}

			for(vector<Unit*>::iterator it = this->units.begin(); it != this->units.end(); ++it)
			{
				Unit* curUnit = (*it);
				
				int x = curUnit->x+20;
				int y = curUnit->y+20;
				

				cout << sX << " " << eX << endl;

				if(x > sX && x < eX && y > sY && y < eY)
				{
					this->selectedUnits.push_back((*it));
				}
			}

		}
	}
}


int Game::getNearAsteroid(Unit* unit)
{
	int nearAsteroid = -1;
	for(int i = 0; i < this->asteroids.size(); i++)
	{		
		int mX = unit->x;
		int mY = unit->y;
		if(mX > this->asteroids[i]->x && mX < this->asteroids[i]->w+this->asteroids[i]->x &&
		   mY > this->asteroids[i]->y && mY < this->asteroids[i]->h+this->asteroids[i]->y)
		{
			nearAsteroid = i;
		}
	}
	return nearAsteroid;
}