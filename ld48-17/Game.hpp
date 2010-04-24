#ifndef GAME_HPP
#define GAME_HPP

#include "Game.hpp"

#include "Asteroid.hpp"
#include "Map.hpp"

enum GameState
{
	Playing,
	Paused,
	Won,
	Lost
};

enum PlayingState
{
	Normal,
	PlacesBuilding
};

class Game
{
	private:
		Gosu::Graphics* graphics;
		Gosu::Input* input;
		Gosu::Font *smallFont;
		Gosu::Font *bigFont;

	public:
		PlayingState playState;
		GameState gameState;

		Map *gamemap;
		vector<Asteroid*> asteroids;

		Game(Gosu::Graphics* graphics, Gosu::Input* input);

		void update();
		void draw();
		void buttonDown(Gosu::Button button);
};

#endif