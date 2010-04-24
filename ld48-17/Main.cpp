#include "Gosu.hpp"
#include "Map.hpp"

using namespace std;

class GosuWindow : public Gosu::Window
{
	private:
		Gosu::Font *font;
		Map *gamemap;

	public:
		GosuWindow()
		 :	Gosu::Window(1024, 768, false)
		{
			setCaption(L"Space Islands!");
			glewInit();

			this->gamemap = new Map(&graphics());
		}

		void draw()
		{
			this->gamemap->draw();
		}

		void update()
		{
			this->gamemap->update();
		}

		void buttonDown(Gosu::Button button)
		{
			if(button == Gosu::kbEscape) close();
		}
};

int main(int argc, char* argv[])
{
    GosuWindow win;
    win.show();

	return 0;
}