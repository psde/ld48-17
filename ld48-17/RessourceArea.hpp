#ifndef RESSOURCEAREA_HPP
#define RESSOURCEAREA_HPP

#include "RessourceRenderer.hpp"

struct Point2D
{
	Point2D(double x, double y)
		: x(x), y(y)
	{ };

	double x, y;
};

class RessourceArea
{
	public:
		Gosu::Graphics* graphics;
		Gosu::Font* smallFont;

		RessourceArea(Gosu::Graphics *graphics)
			: graphics(graphics)
		{
			this->smallFont = new Gosu::Font(*graphics, Gosu::defaultFontName(), 12);
		};

		RessourceType type;
		double availableTons;
		vector<Point2D> area;

		void draw(int x, int y, bool hover=false, int mX=0, int mY=0, RessourceRenderer* resRenderer=0)
		{
			graphics->beginGL();

			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);

			switch(this->type)
			{
				case(Ore):
					glColor4f(0.60f, 0.1f, 0.11f, 1.0f);
					break;
				case(Silicon):
					glColor4f(0.50f, 0.5f, 0.5f, 1.0f);
					break;
				case(Uranium):
					glColor4f(0.20f, 0.6f, 0.11f, 1.0f);
					break;
			}

			glBegin(GL_POLYGON);

			for(vector<Point2D>::iterator itp = this->area.begin(); itp != this->area.end(); ++itp)
			{
				Point2D curPoint = (*itp);
				glVertex2f(curPoint.x + x, curPoint.y + y);
			}

			glEnd();

			if(hover)
			{
				Gosu::Color guiBackground(240, 50, 50, 50);
				Gosu::Color guiBackgroundFade(130, 50, 50, 50);

				graphics->drawQuad(mX+50, mY, guiBackground, mX+160, mY, guiBackground, mX+50, mY+50, guiBackgroundFade, mX+160, mY+50, guiBackgroundFade, 1010);
				this->smallFont->draw(L"RESSOURCE FIELD", mX+62, mY+3,1011);

				resRenderer->draw(mX+55, mY + 15, 1011, this->type);
				this->smallFont->draw(L"" + boost::lexical_cast<std::wstring>(this->availableTons) + L"t left", mX+78, mY+18,1011);
			}

		}
};

#endif