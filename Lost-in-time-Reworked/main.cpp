#include <SFML/Graphics.hpp>
#include <thread>
#include "config.h"
#include "machine.h"

int main()
{
	// Create state machine
	Machine machine;

	// Config file
	Config config;

	// Make the window the game runs in
	sf::RenderWindow* window = new sf::RenderWindow();
	//window->create(sf::VideoMode(config.GetScreenWidth, config.GetScreenHeight), config.GetGameName);
	window->create(sf::VideoMode(1024, 574), "Lost-in-Time-RW");
	window->setFramerateLimit(60);

	while (machine.GetRunning())
		machine.GoNext(*window);

	return 0;
}

void Tick()
{

}