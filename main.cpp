#include "App.h"
#include <cstdlib>
#include <ctime>

int main()
{
	srand(time(nullptr));
	App app;
	while (app.running())
	{
		app.update();
		app.render();
	
	}
}
