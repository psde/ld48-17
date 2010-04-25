#ifndef UNIT_HPP
#define UNIT_HPP

enum UnitType
{
	Scout,
	Colo,
	Cargo
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

		int capacity;
		int cargo[3];


		Unit(int x, int y, UnitType type)
			: x(x), y(y), type(type)
		{
			order = DoNothing;
			speed = 1;
			targetX = x;
			targetY = y;

			cargo[0] = 0;
			cargo[1] = 0;
			cargo[2] = 0;
			
			switch(type)
			{
				case Scout:
					capacity = 10;
					break;

				case Colo:
					capacity = 75;
					break;

				case Cargo:
					capacity = 350;
					break;
			}

		}
		
		int getCapacityLeft()
		{
			int sum = this->cargo[0] + this->cargo[1] + this->cargo[2];
			return (capacity-sum);
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


		static int* getUnitCosts(UnitType type)
		{
			int* foo = new int[3];

			switch(type)
			{
				case Scout:
					foo[0] = 15;
					foo[1] = 5;
					foo[3] = 2;
					break;

				case Colo:
					foo[0] = 120;
					foo[1] = 35;
					foo[3] = 15;
					break;

				case Cargo:
					foo[0] = 75;
					foo[1] = 10;
					foo[3] = 30;
					break;
			}
			return foo;
		}

		static int getUnitBuildTime(UnitType type)
		{
			switch(type)
			{
				case Scout:
					return 500;

				case Colo:
					return 10000;

				case Cargo:
					return 2500;
			}
		}
};

#endif