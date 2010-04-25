
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
		GosuWindow()
		 :	Gosu::Window(1024, 768, false)
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
			this->game->update();
		}

		void buttonDown(Gosu::Button button)
		{
			this->game->buttonDown(button);
			if(button == Gosu::kbEscape) close();
		}

		void buttonUp(Gosu::Button button)
		{
			this->game->buttonUp(button);
		}
};

int main(int argc, char* argv[])
{
    GosuWindow win;
    win.show();

	return 0;
}