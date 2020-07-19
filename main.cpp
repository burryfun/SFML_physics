#include "App.h"

int main()
{
	App app;
	while (app.running())
	{
		app.update();
		app.render();
	
	}
}
