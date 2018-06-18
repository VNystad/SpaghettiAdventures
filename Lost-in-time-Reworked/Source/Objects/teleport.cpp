#include "teleport.h"



Teleport::Teleport(TileSize tileSize, float posX, float posY, bool entry) : Sprite(tileSize)
{
	this->posX = posX;
	this->posY = posY;
	this->entry = entry;
}

void Teleport::collisionAction(Player& player)
{
	// Can player enter teleport?
	if (this->entry)
	{
		// If so, set player position to teleport sister position
		player.SetPositionX(this->GetSisterPosX());
		player.SetPositionY(this->GetSisterPosY());
	}
}


Teleport::~Teleport()
{
}
