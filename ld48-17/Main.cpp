#include "Gosu.hpp"
#include "Game.hpp"


using namespace std;

class GosuWindow : public Gosu::Window
{
	private:
		Gosu::Font *font;

		Gosu::Image* cursor;

		Game* game;

	public:
		GosuWindow()
		 :	Gosu::Window(1024, 768, false)
		{
			setCaption(L"Space Islands!");
			glewInit();

			this->font = new Gosu::Font(graphics(), Gosu::defaultFontName(), 18);

			this->cursor = new Gosu::Image(graphics(), L"data/cursor.png");

			this->game = new Game(&graphics(), &input());

			//
		}

		void draw()
		{
			this->game->draw();
			this->cursor->draw(input().mouseX(), input().mouseY(), 9999);


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
};

int main(int argc, char* argv[])
{
    GosuWindow win;
    win.show();

	return 0;
}