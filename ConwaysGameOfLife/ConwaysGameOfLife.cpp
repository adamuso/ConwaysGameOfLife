// ConwaysGameOfLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Application.h"
#include "MenuView.h"
//#include <vld.h>
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc == 0)
	{
		std::cout << "Nieprawidlowa ilosc argumentow." << std::endl;
		return 1;
	}
	Ref<std::string[]> args = new std::string[argc];

	for (int i = 0; i < argc; i++)
		args[i] = std::string(argv[i]);

	if (argc == 1)
	{
		Ref<Application> app = new Application();
		app->run(new MenuView());
		return 0;
	}

	if (args[1] == "-h" || args[1] == "--help")
	{
		std::cout << "Uzycie: " << std::endl;
		std::cout << "  ConwaysGameOfLife.exe" << std::endl;
		std::cout << "  ConwaysGameOfLife.exe -h | --help" << std::endl;
		std::cout << "  ConwaysGameOfLife.exe <saved-simulation-file>" << std::endl;
		std::cout << std::endl;
		std::cout << "Argumenty: " << std::endl;
		std::cout << "saved-simulation-file   Zapisany plik symulacji." << std::endl;
		std::cout << std::endl;
		std::cout << "Opcje: " << std::endl;
		std::cout << "  -h --help             Pokazuje pomoc." << std::endl;
	}
	else
	{
		Ref<Application> app = new Application();
		app->setOnLoadHandler([args](const Ref<Application>& app) 
		{
			app->getCurrentView().cast<MenuView>()->loadSimulation(args[1]);
		});
		app->run(new MenuView());

		return 0;
	}

	return 0;
}


