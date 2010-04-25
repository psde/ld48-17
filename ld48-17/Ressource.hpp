#ifndef RESSOURCE_HPP
#define RESSOURCE_HPP

enum RessourceType
{
	Ore = 0,
	Silicon = 1,
	Uranium = 2
};

class Ressource
{
	public:
		RessourceType type;

		static RessourceType getType(int i)
		{
			switch(i)
			{
				case 0:
					return Ore;
				case 1:
					return Silicon;
				case 2:
					return Uranium;
			}
		}
};

#endif