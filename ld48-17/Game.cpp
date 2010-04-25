#include "Game.hpp"

Game::Game(Gosu::Graphics* graphics, Gosu::Input* input)
: graphics(graphics), input(input)
{

	this->cursor = new Gosu::Image(*graphics, L"data/cursor.png");

	this->buildRenderer = new BuildingRenderer(graphics);
	this->resRenderer = new RessourceRenderer(graphics);
	this->lineStart = 0;

	this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 14);
	this->bigFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 22);

	/*for(int i = 0; i < 1; i++)
	{
		Asteroid* newAsteroid = new Asteroid(graphics, input, true, 100, 100, 1);
		this->asteroids.push_back(newAsteroid);
	}*/

	Asteroid* newAsteroid1 = new Asteroid(graphics, input, resRenderer, true, 100, 100, 1, true);
	this->asteroids.push_back(newAsteroid1);

	Asteroid* newAsteroid2 = new Asteroid(graphics, input, resRenderer, true, 600, 250, 1);
	this->asteroids.push_back(newAsteroid2);

	this->gamemap = new Map(graphics, 1000);
	this->playState = Normal;
	this->activeAsteroid = 0;
}

void Game::draw()
{
	this->gamemap->draw();

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->draw(*this->buildRenderer, (int)gamemap->x, (int)gamemap->y);
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
	this->buildRenderer->drawProp(Building(0, 0, Depot), 550, 10, 1001);
	this->buildRenderer->drawProp(Building(0, 0, Factory), 600, 10, 1001);

	int* res = this->asteroids[activeAsteroid]->getRessources();
	this->resRenderer->draw(400, 50, 1001, Ore);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[0]), 427, 53, 1001);

	this->resRenderer->draw(500, 50, 1001, Silicon);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[1]), 527, 53, 1001);

	this->resRenderer->draw(600, 50, 1001, Uranium);
	this->smallFont->draw(boost::lexical_cast<std::wstring>(res[2]), 627, 53, 1001);
	

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

	this->cursor->draw((int)input->mouseX(), (int)input->mouseY(), 9999);
}

void Game::update()
{
	this->gamemap->update();

	for(int i = 0; i < this->asteroids.size(); i++)
	{
		this->asteroids[i]->update();

		// check which asteroid

		
		int mX = (int)input->mouseX() + this->gamemap->x;
		int mY = (int)input->mouseY() + this->gamemap->y;
		if(mX > this->asteroids[i]->x && mX < this->asteroids[i]->w+this->asteroids[i]->x &&
		   mY > this->asteroids[i]->y && mY < this->asteroids[i]->h+this->asteroids[i]->y)
		{
			activeAsteroid = i;
		}
	}

	/*for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->update();

		// check which asteroid

		int mX = (int)input->mouseX();
		int mY = (int)input->mouseY();
		if(mX > (*it)->x && mX < (*it)->w && mY > (*it)->y && mY < (*it)->h)
		{
			activeAsteroid = 
		}
		
	}*/

	if(input->down(Gosu::kbLeft)) gamemap->x -= 10;
	if(input->down(Gosu::kbRight)) gamemap->x += 10;
	if(input->down(Gosu::kbUp)) gamemap->y -= 10;
	if(input->down(Gosu::kbDown)) gamemap->y += 10;

	if(gamemap->x < 0) gamemap->x = 0;
	if(gamemap->y < 0) gamemap->y = 0;
	if(gamemap->x > gamemap->size) gamemap->x = gamemap->size;
	if(gamemap->y > gamemap->size) gamemap->y = gamemap->size;
}

void Game::buttonDown(Gosu::Button button)
{
	if(button == Gosu::msRight)
	{
		this->playState = Normal;
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

				case 5:
					this->playState = PlaceBuilding;
					this->placingBuilding = Depot;
					break;

				case 6:
					this->playState = PlaceBuilding;
					this->placingBuilding = Factory;
					break;
			};
		}
		else
		{
			
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
						this->asteroids[activeAsteroid]->addLine(newLine);
						lineStart = 0;
					}
				}
			}

		}
	}
}