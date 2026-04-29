#include "vision/ConsoleMenu.h"
#include <iostream>
namespace vision {

	void runConsoleMenu(AppState& state)
	{
		while (state.running.load()) {
			std::cout << "\n\t===\tRuntime Controle Menu\t===\t\n";
			std::cout << "\t1. Toggle logger\n";
			std::cout << "\t2. Toggle camera\n";
			std::cout << "\t3. Toggle GPU\n";
			std::cout << "\t4. Show status\n";
			std::cout << "\t0. Exit\n";
			std::cout << "> ";

			int choice{};
			std::cin >> choice;

			switch (choice)
			{
			case 1:
				state.loggerEnabled.store(!state.loggerEnabled.load());
				break;

			case 2:
				state.cameraEnabled.store(!state.cameraEnabled.load());
				break;

			case 3:
				state.gpuEnabled.store(!state.gpuEnabled.load());
				break;
			case 4:
				std::cout << "Logger: " << state.loggerEnabled.load() << "\n";
				std::cout << "Camera: " << state.cameraEnabled.load() << "\n";
				std::cout << "GPU: " << state.gpuEnabled.load() << "\n";
				break;

			case 0:
				state.running.store(false);
				break;
			default:
				std::cout << "Unknown option\n";
				break;
			}
		}
	}
}
