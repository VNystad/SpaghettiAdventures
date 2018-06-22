#ifndef OBJECT_H
#define OBJECT_H

#include "../Map/tile.h"

namespace sf
{
	class RenderWindow;
	class Texture;
}

// Small helper struct that contains tile size information
struct TileSize
{
	int x = 32; // Width
	int y = 32; // Height
	int s = 0; // Spacing
};

// Class representing any game object
class Object
{
	// Map needs to access protected/private data
	friend class Map;
	friend class Game;

public:
	// Constructor
	Object(TileSize tileSize) : tileSize(tileSize) { }
	Object() {}
	virtual ~Object();

	virtual void process(float deltaTime) {}
	virtual void draw(sf::RenderWindow& window) {}
	virtual void collisionAction(Object *object) {}

	// Calculate x and y position of given tile in the texture
	void getTileCoords(int tile, int& x, int& y);

	int GetID() { return ID; }
	void SetID(int id) { ID = id; }

	float GetPosX() { return posX; }
	float GetPosY() { return posY; }
	void SetPosX(float x) { posX = x; }
	void SetPosY(float y) { posY = y; }

	const TileSize tileSize;

protected:
	int ID;
	float posX;
	float posY;
	sf::Texture* texture;
};

#endif