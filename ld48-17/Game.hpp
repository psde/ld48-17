#ifndef GAME_HPP
#define GAME_HPP

#include "Game.hpp"

#include "BuildingRenderer.hpp"

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
	PlaceTransportline,
	PlaceEnergyline,
	PlaceBuilding
};


class Game
{
	private:
		Gosu::Graphics* graphics;
		Gosu::Input* input;
		Gosu::Font *smallFont;
		Gosu::Font *bigFont;

		Gosu::Image* cursor;

		BuildingRenderer* buildRenderer;

	public:
		PlayingState playState;
		BuildingType placingBuilding;

		GameState gameState;

		Map *gamemap;
		vector<Asteroid*> asteroids;

		Game(Gosu::Graphics* graphics, Gosu::Input* input);

		void update();
		void draw();
		void buttonDown(Gosu::Button button);
};

#endif