#include <fstream>
#include <cstring>
#include <json/json.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "../Framework/sprite.h"
#include "../Objects/teleport.h"

bool Map::Load(std::string filename, std::list<Object*>& details, int** collidableArray, std::list<SpawnPoint*>& spawnpointList, int** interactionArray, std::map<int, Object*> teleports)
{
	// Will contain the data we read in
	Json::Value root;

	// Parses the file
	//Json::Reader reader;
	Json::CharReaderBuilder rbuilder;

	// Stream used for reading the data file. The data file has been saved as JSON in Tiled
	std::ifstream file(filename);
	std::string errors;

	// Read data from file into root object
	bool parsingSuccessful = Json::parseFromStream(rbuilder, file, &root, &errors);
	if (parsingSuccessful)
	{
		std::cout << "Succesfully read from file into root object." << std::endl << std::endl;
	}

	// Get tile size information
	TileSize tileSize;
	tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
	tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
	tileSize.s = root["tilesets"][0u]["spacing"].asInt();

	// Read in each layer
	for (Json::Value& layer : root["layers"])
	{
		std::string name = layer["name"].asString();
		// All layers that player can collide with should be sent here
		/*if (layer["name"].asString() != "Details" && layer["name"].asString() != "Spawnpoints" )
			LoadLayer(layer, objects, tileSize, collidableArray, interactionArray);*/
		if (layer["name"].asString() == "Collision")
			LoadLayer(layer, details, tileSize, collidableArray);

		// All objects that can be interacted with 
		else if (layer["name"].asString() == "InteractionLocations")
			LoadInteractionObjects(layer, details, tileSize, teleports, interactionArray);

		// all spawnpoints are sent here
		else if (layer["name"].asString() == "Spawnpoints")
			LoadSpawnPoints(root, layer, spawnpointList);

		else
			LoadObjects(root, layer, details, tileSize);
	}

	// Read in tileset (Should be handled by a resource handler)
	sf::Texture* tileset = new sf::Texture();
	tileset->loadFromFile("data/tileset.png");

	// Assign tileset to every object
	for (Object* detail : details)
		detail->texture = tileset;

	return true;
}

void Map::LoadInteractionObjects(Json::Value& layer, std::list<Object*>& details, TileSize tileSize, std::map<int, Object*> teleports, int** interactionArray)
{
	// Iterate over all objects under the "Interaction" layer
	for (Json::Value& object : layer["objects"])
	{
		// If object name is teleport
		if (object["name"].asString() == "Teleport")
		{
			std::string path = "D:\Dev\Lost-in-time-Reworked\Lost-in-time-Reworked\Data\teleport.png";
			Teleport* teleport = new Teleport(object["x"].asInt(), object["y"].asInt(), object["properties"]["Entry"].asBool(), path);
			teleport->SetID(object["id"].asInt());
			teleport->SetSisterTPID(object["properties"]["SisterTeleport"].asInt());
			teleport->SetSisterPosX(object["properties"]["SisterTeleportX"].asFloat());
			teleport->SetSisterPosY(object["properties"]["SisterTeleportY"].asFloat());

			int id = object["id"].asInt();

			teleports.emplace(id, teleport);

			//details.push_back(teleport);
			
			// Add to interactionArray to identify collision
			int x = (object["x"].asInt() + 32)/32;
			int y = (object["y"].asInt() - 32)/32;
			interactionArray[y][x] = object["id"].asInt();
			continue;
		}
	}
}

void Map::LoadLayer(Json::Value& layer, std::list<Object*>& details, TileSize tileSize, int** collidableArray)
{
	Layer* tmp = new Layer(tileSize);

	// Store info on layer
	tmp->width = layer["width"].asInt();
	tmp->height = layer["height"].asInt();

	// Clear tilemap
	memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

	// Read in tilemap
	for (size_t i = 0; i < layer["data"].size(); i++)
	{
		tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int)i].asInt();


	}

	if ((layer["name"].asString() == "Collision"))
	{
		int count = 0;

		// Add tile id to array from layer"data"
		for (int y = 0; y < tmp->height; y++)
		{
			for (int x = 0; x < tmp->width; x++)
			{
				collidableArray[y][x] = layer["data"][count].asInt();
				count++;
			}
		}
	}

	details.push_back(tmp);
}

void Map::LoadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& details, TileSize tileSize)
{
	// Get all objects from layer
	for (Json::Value& object : layer["objects"])
	{
		Sprite* sprite = new Sprite(tileSize);

		// Load basic object info
		sprite->x = object["x"].asInt();
		sprite->y = object["y"].asInt() - sprite->tileSize.y;
		sprite->id = object["gid"].asInt();

		// Load animation data
		Json::Value& tileInfo = root["tilesets"][0u]["tiles"][std::to_string(sprite->id - 1)];
		sprite->frame = 0;
		sprite->frameCount = tileInfo["animation"].size();
		sprite->frameDuration = tileInfo["animation"][0u]["duration"].asInt();

		details.push_back(sprite);
	}

}

void Map::LoadSpawnPoints(Json::Value& root, Json::Value& layer, std::list<SpawnPoint*>& spawnpointList)
{
	// Get all spawnpoints from spawnPoint layer
	for (Json::Value& object : layer["objects"])
	{
		SpawnPoint* spawnPoint = new SpawnPoint();

		spawnPoint->typeOfObject = object["name"].asString();
		spawnPoint->x = object["x"].asFloat();
		spawnPoint->y = object["y"].asFloat();
		spawnPoint->patrol = object["properties"]["patrol"].asInt();

		spawnpointList.push_back(spawnPoint);
	}
}