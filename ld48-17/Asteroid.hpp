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

		RessourceRenderer* resRenderer;

		Gosu::Image* img;
		Gosu::Image* imgBuildMap;
		Gosu::Bitmap buildMap;


		vector<RessourceArea*> ressourceAreas;
		vector<Building*> buildings;

		vector<Line*> lines;

		int hover;
		int maxHover;

	public:
		const bool capturable;
		double x, y, w, h;

		Asteroid(Gosu::Graphics* graphics, Gosu::Input* input, RessourceRenderer* resRenderer, bool capturable, double x, double y, int type, bool start=false);
		

		void draw(BuildingRenderer &buildRenderer, int scrollX, int scrollY);
		void update();

		bool isFree(int x, int y);
		void placeBuilding(int x, int y, BuildingType type);

		Building* getBuildingAt(int x, int y, int scrollX, int scrollY);
		void addLine(Line* l);

		bool isInsideRessourceArea(int x, int y, RessourceArea* curArea);
		RessourceArea* getRessourceAreaAt(int x, int y);

		int* getRessources();
};

#endif