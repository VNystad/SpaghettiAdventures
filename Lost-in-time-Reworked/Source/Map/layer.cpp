#include <SFML/Graphics.hpp>
#include <iostream>

#include "layer.h"

void Layer::draw(sf::RenderWindow& window)
{
	sf::View view = window.getView();
	int windowWidt = window.getSize().x;
	int windowHeight = window.getSize().y;
	int viewPosX = view.getCenter().x;
	int viewPosY = view.getCenter().y;


	// Finne koordinatene ytters på view
	int lowerX = (int)(view.getCenter().x - window.getSize().x / 2) / 32;
	int lowerY = (int)(view.getCenter().y - window.getSize().y / 2) / 32;

	int upperX = (int)(view.getCenter().x + window.getSize().x / 2) / 32 + 2;
	int upperY = (int)(view.getCenter().y + window.getSize().y / 2) / 32 + 2;

	// Render only tiles in view of window
	for (int y = lowerY; y < upperY; y++)
	{
		if (y < 0)
			continue;
		for (int x = lowerX; x < upperX; x++)
		{
			if (x < 0)
				continue;
			// Skip empty tiles
			if (tilemap[x][y] == 0)
				continue;


			int tileid = tilemap[x][y];

			// Texture coordinates
			int tilex, tiley;
			getTileCoords(tileid, tilex, tiley);
			/*
			if(count < height * width)
			{
			++count;
			//collidableArray[y][x] = tileid;
			}*/

			// Using vertex arrays or permanent sprites would be faster
			sf::Sprite sprite(*texture, sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));
			sprite.setPosition((float)(x * tileSize.x), (float)(y * tileSize.y));
			int posX = x * tileSize.x;
			int posY = y * tileSize.y;

			window.draw(sprite);
		}
	}
}