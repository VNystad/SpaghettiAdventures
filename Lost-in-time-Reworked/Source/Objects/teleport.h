#pragma once

#include "player.h"
#include "../Framework/sprite.h"
#include <list>

class Teleport : public Sprite
{
public:
	Teleport(TileSize tileSize, float posX, float posY, bool entry);
	~Teleport();

	void collisionAction(Player& player);


	void SetSisterPosX(float posX) { sisterPosX = posX; }
	void SetSisterPosY(float posY) { sisterPosY = posY; }
	float GetSisterPosX() { return sisterPosX; }
	float GetSisterPosY() { return sisterPosY; }

	
	void SetID(int id) { teleportID = id; }
	int GetID() { return teleportID; }

protected:
	// Can enter teleport?
	bool entry;

	float sisterPosX;
	float sisterPosY;
	int teleportID;
};

