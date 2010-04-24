#include "Game.hpp"

Game::Game(Gosu::Graphics* graphics, Gosu::Input* input)
: graphics(graphics), input(input)
{

	this->cursor = new Gosu::Image(*graphics, L"data/cursor.png");

	this->buildRenderer = new BuildingRenderer(graphics);

	this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 14);
	this->bigFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 22);

	for(int i = 0; i < 1; i++)
	{
		Asteroid* newAsteroid = new Asteroid(graphics, true, 100, 100, 1);
		this->asteroids.push_back(newAsteroid);
	}
	this->gamemap = new Map(graphics, 1000);
	this->playState = Normal;
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

	bool testFree = this->asteroids[0]->isFree((int)input->mouseX()-120, (int)input->mouseY()-120);
	this->smallFont->draw(L"free? " +  boost::lexical_cast<std::wstring>(testFree), 10, 60, 9999);


	// GUI:
	Gosu::Color guiBackground(240, 50, 50, 50);
	Gosu::Color guiBackgroundFade(130, 50, 50, 50);
	graphics->drawQuad(250, 0, guiBackground, 774, 0, guiBackground, 250, 70, guiBackgroundFade, 774, 70, guiBackgroundFade, 1000);
	
	this->cursor->draw(320, 20, 1001);
	graphics->drawLine(360, 20, Gosu::Colors::aqua, 380, 40, Gosu::Colors::aqua, 1001);
	graphics->drawLine(410, 20, Gosu::Colors::red, 430, 40, Gosu::Colors::red, 1001);
	this->buildRenderer->draw(Building(0, 0, EnergyCollector), 450, 10, 1001);
	this->buildRenderer->draw(Building(0, 0, Mine), 500, 10, 1001);
	this->buildRenderer->draw(Building(0, 0, Depot), 550, 10, 1001);
	

/*
	GosuEx::Shader local(*graphics);
	static GosuEx::ShaderProgram program = local.compile(L"data/shader/ressourceArea.frag");
*/

	this->cursor->draw(input->mouseX(), input->mouseY(), 9999);
}

void Game::update()
{
	this->gamemap->update();

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->update();
	}

	if(input->down(Gosu::kbLeft)) gamemap->x -= 5;
	if(input->down(Gosu::kbRight)) gamemap->x += 5;
	if(input->down(Gosu::kbUp)) gamemap->y -= 5;
	if(input->down(Gosu::kbDown)) gamemap->y += 5;

	if(gamemap->x < 0) gamemap->x = 0;
	if(gamemap->y < 0) gamemap->y = 0;
	if(gamemap->x > gamemap->size) gamemap->x = gamemap->size;
	if(gamemap->y > gamemap->size) gamemap->y = gamemap->size;
}

void Game::buttonDown(Gosu::Button button)
{
	if(button == Gosu::msLeft)
	{
		// check if inside of gui
		int x = (int)input->mouseX();
		int y = (int)input->mouseY();

		if(x > 250 && x < 774 && y > 0 && y < 70)
		{	
			int selection = -1;
			for(int i = 0; i < 6; i++)
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
					break;

				case 2:
					this->playState = PlaceEnergyline;
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
			};
		}
		else
		{
			
			if(this->playState == PlaceBuilding)
			{
				this->asteroids[0]->placeBuilding((int)input->mouseX()-this->asteroids[0]->x - 20, (int)input->mouseY()-this->asteroids[0]->y - 20, this->placingBuilding);
			}

		}
	}
}