#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Gosu.hpp"
#include "RessourceArea.hpp"
#include "Building.hpp"

class Asteroid
{
	private:
		Gosu::Graphics* graphics;
		Gosu::Image* img;
		Gosu::Image* imgBuildMap;
		Gosu::Bitmap buildMap;


		vector<RessourceArea> ressourceAreas;
		vector<Building> buildings;


		Gosu::Image* buildingBackdrop;
		Gosu::Image* buildingEnergy;

	public:
		const bool capturable;
		double x, y;

		Asteroid(Gosu::Graphics* graphics, bool capturable, double x, double y, int type);
		

		void draw();
		void update();

		bool isFree(int x, int y);
		void Asteroid::placeBuilding(int x, int y);
};

#endif