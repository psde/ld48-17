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

		vector<Line*> powerlines;
		vector<Line*> transportlines;

		int hover;
		int maxHover;


	public:
		const bool capturable;
		bool scouted;
		double x, y, w, h;

		double depotStartX, depotStartY;

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
		bool reduceRessources(int r1, int r2, int r3);

		
		int* getBuildingCost(BuildingType type);
		int* getBuildingCost(int type);

		Building* getDepot();
		bool hasSpaceport();

		bool colonize();
};

#endif