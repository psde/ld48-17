#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Gosu.hpp"
#include "BuildingRenderer.hpp"
#include "RessourceArea.hpp"
#include "Building.hpp"
#include "Line.hpp"


class Asteroid
{
	private:
		Gosu::Graphics* graphics;
		Gosu::Input* input;

		Gosu::Image* img;
		Gosu::Image* imgBuildMap;
		Gosu::Bitmap buildMap;


		vector<RessourceArea*> ressourceAreas;
		vector<Building*> buildings;

		vector<Line*> lines;

	public:
		const bool capturable;
		double x, y;

		Asteroid(Gosu::Graphics* graphics, Gosu::Input* input, bool capturable, double x, double y, int type);
		

		void draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY);
		void update();

		bool isFree(int x, int y);
		void placeBuilding(int x, int y, BuildingType type);

		Building* getBuildingAt(int x, int y, int scrollX, int scrollY);
		void addLine(Line* l);

		RessourceArea* getRessourceAreaAt(int x, int y);
};

#endif