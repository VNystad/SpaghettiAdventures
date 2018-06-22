#pragma once

#include "player.h"
#include <list>

class Teleport : public Object
{
public:
	Teleport(float posX, float posY, bool entry, std::string texturePath);
	~Teleport();

	void collisionAction(Object* player);
	void draw(sf::RenderWindow& window);

	void SetSisterPosX(float posX) { sisterPosX = posX; }
	void SetSisterPosY(float posY) { sisterPosY = posY; }

	Teleport* GetSisterTeleport() { return sisterTeleport; }
	float GetSisterPosX() { return sisterPosX; }
	float GetSisterPosY() { return sisterPosY; }

	
	void SetSisterTPID(int id) { sisterTPID = id; }
	int GetSisterTPID() { return sisterTPID; }

protected:
	sf::Texture texture;
	sf::Sprite sprite;


	// Can enter teleport?
	bool entry;

	Teleport* sisterTeleport;
	float sisterPosX;
	float sisterPosY;
	int sisterTPID;
};

