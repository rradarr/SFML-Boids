#include <iostream>

#include <SFML/Graphics.hpp>

#include "Application.h"


int main()
{
	{
		Application app;

		app.InitializeApplication(100, 2);

		while (app.IsRunning())
		{
			app.ProcessInput();
			//std::cout << "input processed" << std::endl;
			app.Update();
			//std::cout << "updated" << std::endl;
			app.LateUpdate();
			//std::cout << "late updated" << std::endl;
			app.Draw();
			//std::cout << "drawn" << std::endl;
			app.GetDeltaTime();
			//std::cout << "got delta" << std::endl;
		}

		return 0;
	}
}