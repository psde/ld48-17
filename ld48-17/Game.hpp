#ifndef GAME_HPP
#define GAME_HPP



#include "BuildingRenderer.hpp"
#include "RessourceRenderer.hpp"

#include "Asteroid.hpp"
#include "Map.hpp"

#include "Unit.hpp"
#include "UnitRenderer.hpp"

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
		RessourceRenderer* resRenderer;
		UnitRenderer* unitRenderer;

		Building* lineStart;
		Asteroid* lineAsteroid;

		int activeAsteroid;

	public:
		PlayingState playState;
		BuildingType placingBuilding;

		GameState gameState;

		Map *gamemap;
		vector<Asteroid*> asteroids;
		vector<Unit*> units;
		vector<Unit*> selectedUnits;
		Point2D selectStart;
		bool selecting;

		Game(Gosu::Graphics* graphics, Gosu::Input* input);

		void update();
		void draw();
		void buttonDown(Gosu::Button button);
		void buttonUp(Gosu::Button button);


		bool isUnitSelected(Unit* unit);

};

#endif