/*
##############################################################################
+ class Shape от которого наследуются фигуры
+ Пофиксить положение объекта за экраном
+ Добавить gui(SFGUI)
###############################################################################
*/

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
