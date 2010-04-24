#include "Gosu.hpp"

using namespace std;

class GosuWindow : public Gosu::Window
{
	private:
		Gosu::Font *font;

	public:
		GosuWindow()
		 :	Gosu::Window(800, 600, false)
		{
			setCaption(L"Islands!");
			glewInit();
		}

		void draw()
		{

		}

		void update()
		{

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