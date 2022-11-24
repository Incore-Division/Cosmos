#include <iostream>
#include <filesystem>

#include <Engine.h>

int main(int argc, char* argv[])
{
	std::cout << std::filesystem::current_path().string() << std::endl;

	Cosmos::Application* app = new Cosmos::Application();
	app->Run();
	delete app;

	return 0;
}