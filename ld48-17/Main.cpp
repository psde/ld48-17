
// FUCK DIS SHIT
// next time I will try ruby
// c++ fuckage




#include "Gosu.hpp"
#include "Game.hpp"


using namespace std;

class GosuWindow : public Gosu::Window
{
	private:
		Gosu::Font *font;


		Game* game;

	public:
		GosuWindow(bool fullscreen)
		 :	Gosu::Window(1024, 768, fullscreen)
		{
			setCaption(L"Space Islands!");
			glewInit();

			this->font = new Gosu::Font(graphics(), Gosu::defaultFontName(), 18);


			this->game = new Game(&graphics(), &input());

			//
		}

		void draw()
		{
			this->game->draw();


		}

		void update()
		{
			if(this->game->update())
			{
				close();
			}
		}

		void buttonDown(Gosu::Button button)
		{
			this->game->buttonDown(button);
			//if(button == Gosu::kbEscape) close();
		}

		void buttonUp(Gosu::Button button)
		{
			this->game->buttonUp(button);
		}
};

int main(int argc, char* argv[])
{
	bool fullscreen = false;
	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i], "-fullscreen") == 0) fullscreen = true;
	}

    GosuWindow win(fullscreen);
    win.show();

	return 0;
}