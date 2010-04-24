#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Gosu.hpp"
#include "BuildingRenderer.hpp"
#include "RessourceArea.hpp"
#include "Building.hpp"

class Asteroid
{
	private:
		Gosu::Graphics* graphics;
		Gosu::Input* input;

		Gosu::Image* img;
		Gosu::Image* imgBuildMap;
		Gosu::Bitmap buildMap;


		vector<RessourceArea> ressourceAreas;
		vector<Building> buildings;

	public:
		const bool capturable;
		double x, y;

		Asteroid(Gosu::Graphics* graphics, Gosu::Input* input, bool capturable, double x, double y, int type);
		

		void draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY);
		void update();

		bool isFree(int x, int y);
		void placeBuilding(int x, int y, BuildingType type);
};

#endif