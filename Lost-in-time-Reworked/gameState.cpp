#include "gameState.h"
#include "machine.h"
#include "levelOne.h"

void GameState::GoNext(Machine &machine, sf::RenderWindow& window)
{
	LevelOne levelOne(window);

	while (levelOne.Tick(machine));
}