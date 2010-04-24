#ifndef RESSOURCEAREA_HPP
#define RESSOURCEAREA_HPP

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

		RessourceArea(Gosu::Graphics *graphics)
			: graphics(graphics)
		{

		};

		RessourceType type;
		double availableTons;
		vector<Point2D> area;

		void draw(int x, int y)
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
		}
};

#endif