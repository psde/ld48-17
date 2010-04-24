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
		int type;
		double availableTons;
		vector<Point2D> area;
};

#endif