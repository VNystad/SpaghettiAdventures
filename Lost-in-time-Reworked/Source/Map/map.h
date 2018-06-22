#ifndef MAP_H
#define MAP_H

#include <string>
#include <list>
#include <map>
#include "../Objects/teleport.h"
#include "layer.h"
#include "spawnpoint.h"

namespace Json
{
	class Value;
}

// Class with a single public static function that loads a map into an object list
class Map
{
public:
	// Construtor
	Map() { }

	// Load map from Tiled JSON file
	static bool Load(std::string filename, std::list<Object*>& details, int** collidableArray, std::list<SpawnPoint*>& spawnpointList, int** interactionArray, std::map<int, Object*> teleports);

private:

	// Handles regular layers
	static void LoadLayer(Json::Value& layer, std::list<Object*>& details, TileSize tileSize, int** collidableArray);

	// Handles interaction object layers
	static void LoadInteractionObjects(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize, std::map<int, Object*> teleports, int** interactionArray);

	// Handles object layers
	static void LoadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& details, TileSize tileSize);

	// Handles spawn points
	static void LoadSpawnPoints(Json::Value& root, Json::Value& layer, std::list<SpawnPoint*>& spawnpoint);
};

#endif