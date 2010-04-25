#ifndef UNIT_HPP
#define UNIT_HPP

enum UnitType
{
	Scout,
	Colo
};

enum UnitOrder
{
	DoNothing,
	DoMove,
	DoScout,
	DoColo
};

class Unit
{
	public:
		double x,y;
		UnitType type;
		UnitOrder order;

		double speed;
		double targetX, targetY;


		Unit(int x, int y, UnitType type)
			: x(x), y(y), type(type)
		{
			order = DoNothing;
			speed = 1;
			targetX = x;
			targetY = y;
		}


		void update()
		{
			if(order != DoNothing)
			{
				if(Gosu::distance(x, y, targetX, targetY) > 2)
				{
					double a = this->x - this->targetX;
					double b = this->y - this->targetY;
					double angle = atan2(b, a);

					this->x += cos(angle) * -speed;
					this->y += sin(angle) * -speed;
				}
				else
				{
					order = DoNothing;
					targetX = x;
					targetY = y;
				}
			}
		}

};

#endif