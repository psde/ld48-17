#ifndef BUILDINGRENDERER_HPP
#define BUILDINGRENDERER_HPP

#include "Gosu.hpp"
#include "Building.hpp"

class BuildingRenderer
{
	private:
		Gosu::Graphics* graphics;

		Gosu::Image* backdrop;
		Gosu::Image* energy;
		Gosu::Image* depot;
		Gosu::Image* mine;

		Gosu::Font* smallFont;

	public:
		BuildingRenderer(Gosu::Graphics* graphics)
			: graphics(graphics)
		{
			this->backdrop = new Gosu::Image(*graphics, L"data/buildings/backdrop.png");
			this->energy = new Gosu::Image(*graphics, L"data/buildings/energy.png");
			this->depot = new Gosu::Image(*graphics, L"data/buildings/depot.png");
			this->mine = new Gosu::Image(*graphics, L"data/buildings/mine.png");

			this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 12);
		};

		void draw(Building* build, int x, int y, int z, bool hovering, int status=0)
		{
			Gosu::Color c = Gosu::Colors::white;

			if(status == 1) c = Gosu::Colors::red;
			if(status == 2) c = Gosu::Colors::green;

			this->backdrop->draw(x, y, z, 1, 1, c);
			z++;
			switch(build->type)
			{
				case EnergyCollector:
					this->energy->draw(x, y, z, 1, 1, c);
					break;
				case Mine:
					this->mine->draw(x, y, z, 1, 1, c);
					break;
				case Depot:
					this->depot->draw(x, y, z, 1, 1, c);
					break;
			};

			if(hovering)
			{
				// draw building information

				Gosu::Color guiBackground(240, 50, 50, 50);
				Gosu::Color guiBackgroundFade(130, 50, 50, 50);

				graphics->drawQuad(x+50, y, guiBackground, x+200, y, guiBackground, x+50, y+200, guiBackgroundFade, x+200, y+200, guiBackgroundFade, 1010);
				this->smallFont->draw(L"Type: " + boost::lexical_cast<std::wstring>(build->type),x+60, y+10, 1011);
				this->smallFont->draw(L"Energy Sup: " + boost::lexical_cast<std::wstring>(build->energySupplied),x+60, y+20, 1011);
				this->smallFont->draw(L"Energy Req: " + boost::lexical_cast<std::wstring>(build->energyRequirement),x+60, y+30, 1011);
				this->smallFont->draw(L"Energy In: " + boost::lexical_cast<std::wstring>(build->energyIn),x+60, y+40, 1011);
				this->smallFont->draw(L"Energy Out: " + boost::lexical_cast<std::wstring>(build->energyOut),x+60, y+50, 1011);
				this->smallFont->draw(L"Transport In: " + boost::lexical_cast<std::wstring>(build->transportIn.type),x+60, y+60, 1011);
				this->smallFont->draw(L"Transport Out: " + boost::lexical_cast<std::wstring>(build->transportOut.type),x+60, y+70, 1011);

			}
		}

		void drawProp(Building& build, int x, int y, int z)
		{
			Gosu::Color c = Gosu::Colors::white;


			this->backdrop->draw(x, y, z, 1, 1, c);
			z++;
			switch(build.type)
			{
				case EnergyCollector:
					this->energy->draw(x, y, z, 1, 1, c);
					break;
				case Mine:
					this->mine->draw(x, y, z, 1, 1, c);
					break;
				case Depot:
					this->depot->draw(x, y, z, 1, 1, c);
					break;
			};
		}

};

#endif