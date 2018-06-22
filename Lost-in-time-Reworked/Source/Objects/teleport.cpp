#include "teleport.h"



Teleport::Teleport(float posX, float posY, bool entry, std::string texturePath)
{
	this->posX = posX;
	this->posY = posY;
	this->entry = entry;
	texture.loadFromFile(texturePath);
	sprite.setTexture(texture);
	sprite.setPosition(sf::Vector2f(posX, posY));
}

void Teleport::collisionAction(Object* player)
{
	// Can player enter teleport?
	if (this->entry)
	{
		// If so, set player position to teleport sister position
		player->SetPosX(this->GetSisterPosX());
		player->SetPosY(this->GetSisterPosY());
	}
}

void Teleport::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

Teleport::~Teleport()
{
	this->sisterTeleport = NULL;
}
