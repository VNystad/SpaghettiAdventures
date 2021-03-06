#ifndef LOST_IN_TIME_MACHINE_H
#define LOST_IN_TIME_MACHINE_H

#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

class State;

class Machine
{
public:
	// Different states
	enum class StateId { MAINMENU, LOAD, GAME };

	Machine();
	~Machine();

	// Function that goes to the next state
	void GoNext(sf::RenderWindow& window);

	// Sets the new state
	void SetState(StateId state);

	bool GetRunning() const { return running; }
	void SetRunning(bool running) { this->running = running; }

protected:
	bool running;
	StateId state;
	std::map<StateId, State*> states;
};


#endif