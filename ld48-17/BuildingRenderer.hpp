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
		Gosu::Image* factory;
		Gosu::Image* spaceport;

		Gosu::Font* smallFont;

	public:
		BuildingRenderer(Gosu::Graphics* graphics)
			: graphics(graphics)
		{
			this->backdrop = new Gosu::Image(*graphics, L"data/buildings/backdrop.png");
			this->energy = new Gosu::Image(*graphics, L"data/buildings/energy.png");
			this->depot = new Gosu::Image(*graphics, L"data/buildings/depot.png");
			this->mine = new Gosu::Image(*graphics, L"data/buildings/mine.png");
			this->factory = new Gosu::Image(*graphics, L"data/buildings/factory.png");
			this->spaceport = new Gosu::Image(*graphics, L"data/buildings/spaceport.png");


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
				case Factory:
					this->factory->draw(x, y, z, 1, 1, c);
					break;
				case Spaceport:
					this->spaceport->draw(x, y, z, 1, 1, c);
					break;
			};

			if(build->energyRequirement != -1 && build->energyIn != build->energyRequirement)
			{
				this->energy->draw(x+10, y-10, z, 0.7f, 0.7f, c);
			}

			if(hovering)
			{
				// draw building information

				Gosu::Color guiBackground(240, 50, 50, 50);
				Gosu::Color guiBackgroundFade(130, 50, 50, 50);

				int length=-1;
				int height=25;

				wstring inBuild = L"";

				switch(build->type)
				{
					case EnergyCollector:
						this->smallFont->draw(L"Energy collector:",x+53, y+3, 1011);
						this->smallFont->draw(L"Output: " + boost::lexical_cast<std::wstring>(build->energyOut) + L"mW",x+53, y+13, 1011);
						length = 95;
						height = 30;
						break;
					case Mine:
						this->smallFont->draw(L"Harvester:",x+53, y+3, 1011);
						this->smallFont->draw(L"every " + boost::lexical_cast<std::wstring>(build->maxTick) + L" tick",x+53, y+13, 1011);
						this->smallFont->draw(L"Energy: " + boost::lexical_cast<std::wstring>(build->energyIn) + L" / " + boost::lexical_cast<std::wstring>(build->energyRequirement) ,x+53, y+23, 1011);
						length = 95;
						height = 40;
						break;
					case Depot:
						this->smallFont->draw(L"Depot:",x+53, y+3, 1011);
						this->smallFont->draw(L"Energy: " + boost::lexical_cast<std::wstring>(build->energyIn) + L" / " + boost::lexical_cast<std::wstring>(build->energyRequirement) ,x+53, y+13, 1011);
						this->smallFont->draw(L"Ore: " + boost::lexical_cast<std::wstring>(build->internalDepot[0]) + L"",x+53, y+23, 1011);
						this->smallFont->draw(L"Silicon: " + boost::lexical_cast<std::wstring>(build->internalDepot[1]) + L"",x+53, y+33, 1011);
						this->smallFont->draw(L"Uranium: " + boost::lexical_cast<std::wstring>(build->internalDepot[2]) + L"",x+53, y+43, 1011);
						length = 95;
						height = 60;
						break;
					case Factory:
						this->smallFont->draw(L"Factory:",x+53, y+3, 1011);
						this->smallFont->draw(L"Energy: " + boost::lexical_cast<std::wstring>(build->energyIn) + L" / " + boost::lexical_cast<std::wstring>(build->energyRequirement) ,x+53, y+13, 1011);

						switch(build->unitInBuild)
						{
							case Scout:
								inBuild = L"Scout";
								break;
							case Cargo:
								inBuild = L"Cargoship";
								break;
							case Colo:
								inBuild = L"Coloship";
								break;
							case NoUnit:
								inBuild = L"Nothing";
								break;
						}

						this->smallFont->draw(L"Currenty builds:",x+53, y+23, 1011);
						this->smallFont->draw(L" " + inBuild,x+53, y+33, 1011);
						if(build->unitInBuild != NoUnit) this->smallFont->draw(L"Completed: " + boost::lexical_cast<std::wstring>(build->tick) + L" / " + boost::lexical_cast<std::wstring>(build->maxTick),x+53, y+43, 1011);

						this->smallFont->draw(L"Ressources needed:",x+53, y+63, 1011);
						this->smallFont->draw(L"Ore: " +  boost::lexical_cast<std::wstring>(build->wantsRes[0]),x+53, y+73, 1011);
						this->smallFont->draw(L"Silicon: " + boost::lexical_cast<std::wstring>(build->wantsRes[1]),x+53, y+83, 1011);
						this->smallFont->draw(L"Uranium: " + boost::lexical_cast<std::wstring>(build->wantsRes[2]),x+53, y+93, 1011);
						length = 100;
						height = 110;
						break;

					case Spaceport:
						this->smallFont->draw(L"Spaceport:",x+53, y+3, 1011);
						this->smallFont->draw(L"Energy: " + boost::lexical_cast<std::wstring>(build->energyIn) + L" / " + boost::lexical_cast<std::wstring>(build->energyRequirement) ,x+53, y+13, 1011);
						length = 90;
						break;
				};

				if(length != -1) graphics->drawQuad(x+50, y, guiBackground, x+50+length, y, guiBackground, x+50, y+height, guiBackgroundFade, x+50+length, y+height, guiBackgroundFade, 1010);

				/*graphics->drawQuad(x+50, y, guiBackground, x+200, y, guiBackground, x+50, y+200, guiBackgroundFade, x+200, y+200, guiBackgroundFade, 1010);
				this->smallFont->draw(L"Type: " + boost::lexical_cast<std::wstring>(build->type),x+60, y+10, 1011);
				this->smallFont->draw(L"Energy Sup: " + boost::lexical_cast<std::wstring>(build->energySupplied),x+60, y+20, 1011);
				this->smallFont->draw(L"Energy Req: " + boost::lexical_cast<std::wstring>(build->energyRequirement),x+60, y+30, 1011);
				this->smallFont->draw(L"Energy In: " + boost::lexical_cast<std::wstring>(build->energyIn),x+60, y+40, 1011);
				this->smallFont->draw(L"Energy Out: " + boost::lexical_cast<std::wstring>(build->energyOut),x+60, y+50, 1011);
				this->smallFont->draw(L"Transport In: " + boost::lexical_cast<std::wstring>(build->transportIn.type),x+60, y+60, 1011);
				this->smallFont->draw(L"Transport Out: " + boost::lexical_cast<std::wstring>(build->transportOut.type),x+60, y+70, 1011);
				this->smallFont->draw(L"Tick: " + boost::lexical_cast<std::wstring>(build->tick),x+60, y+80, 1011);
				this->smallFont->draw(L"max tick: " + boost::lexical_cast<std::wstring>(build->maxTick),x+60, y+90, 1011);
				this->smallFont->draw(L"1: " + boost::lexical_cast<std::wstring>(build->internalDepot[0]),x+60, y+100, 1011);
				this->smallFont->draw(L"2: " + boost::lexical_cast<std::wstring>(build->internalDepot[1]),x+60, y+110, 1011);
				this->smallFont->draw(L"3: " + boost::lexical_cast<std::wstring>(build->internalDepot[2]),x+60, y+120, 1011);*/

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
				case Factory:
					this->factory->draw(x, y, z, 1, 1, c);
					break;
				case Spaceport:
					this->spaceport->draw(x, y, z, 1, 1, c);
					break;
			};
		}

};

#endif