#include "Game.hpp"

Game::Game(Gosu::Graphics* graphics, Gosu::Input* input)
: graphics(graphics), input(input)
{

	this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 14);
	this->bigFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 22);

	for(int i = 0; i < 1; i++)
	{
		Asteroid* newAsteroid = new Asteroid(graphics, true, 100, 100, 1);
		this->asteroids.push_back(newAsteroid);
	}
	this->gamemap = new Map(graphics, 1000);
}

void Game::draw()
{
	this->gamemap->draw();

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->draw();
	}

	this->smallFont->draw(L"x: " +  boost::lexical_cast<std::wstring>(gamemap->x), 10, 10, 9999);
	this->smallFont->draw(L"y: " +  boost::lexical_cast<std::wstring>(gamemap->y), 10, 20, 9999);

	bool testFree = this->asteroids[0]->isFree(input->mouseX()-120, input->mouseY()-120);
	this->smallFont->draw(L"free? " +  boost::lexical_cast<std::wstring>(testFree), 10, 40, 9999);
}

void Game::update()
{
	this->gamemap->update();

	for(vector<Asteroid*>::iterator it = this->asteroids.begin(); it != this->asteroids.end(); ++it)
	{
		(*it)->update();
	}

}

void Game::buttonDown(Gosu::Button button)
{
	if(button == Gosu::msLeft)
	{
		this->asteroids[0]->placeBuilding(input->mouseX()-this->asteroids[0]->x - 20, input->mouseY()-this->asteroids[0]->y - 20);
	}
}