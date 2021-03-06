#ifndef LOST_IN_TIME_LEVELONE_H
#define LOST_IN_TIME_LEVELONE_H


#include <list>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "level.h"
#include "../Framework/config.h"
#include "../Map/map.h"
#include "../States/machine.h"
#include "../Objects/player.h"
#include "../Objects/teleport.h"
//#include "camera.h"


class LevelOne
{
public:
	LevelOne(sf::RenderWindow& window);
	~LevelOne();

	void AttemptTeleport(Player* player);

	bool Tick(Machine& machine);
	void RenderMap(float delta);
	void PositionCamera();
	void Move(float delta);
	void AIHandler(float delta);

	bool EscMenu(Machine& machine); // Menu when u press Esc
	//bool SaveGame(int selectedSave); // Function under the Esc menu, savegame
	int menuSelected(std::string menu); // Function to choose in menus

	void LoadImages();

	sf::Texture* LoadTexture(std::string path, int &menuAmount); // Function to load in textures

protected:
	bool keyPressed = false;
	bool playerNamed = false;
	bool attack = true;
	bool noAttack = false;

	/***************
	* List of Items
	**************/
	//std::list<Item>* items;
	//std::vector<Item>* items;

	/****************
	*  Victory stuff
	****************/
	// princess?
	/*bool princessSpawn = false;
	sf::Text* victoryText;
	sf::Text* secretText;
	sf::Texture* heart = nullptr;
	sf::Sprite heartSprite;
	int timeFromLoad = 0;*/
	std::string playerName;
	int time = 0;

	/***********************
	* Variables for EscMenu
	**********************/
	// Text for name
	sf::Text* name;
	// The amount of saves
	//int amountOfSaves = 0;
	// The amount of options in EscMenu
	//int amountOfEscOptions = 0;

	/*sf::Texture* save1 = nullptr;
	sf::Texture* save2 = nullptr;
	sf::Texture* save3 = nullptr;
	sf::Texture* save1Selected = nullptr;
	sf::Texture* save2Selected = nullptr;
	sf::Texture* save3Selected = nullptr;

	sf::Texture* resumeGame = nullptr;
	sf::Texture* resumeGameSelected = nullptr;
	sf::Texture* saveGame = nullptr;
	sf::Texture* saveGameSelected = nullptr;
	sf::Texture* mainMenu = nullptr;
	sf::Texture* mainMenuSelected = nullptr;
	sf::Texture* exitGame = nullptr;
	sf::Texture* exitGameSelected = nullptr;

	sf::Sprite save1Sprite;
	sf::Sprite save2Sprite;
	sf::Sprite save3Sprite;
	sf::Sprite save1SelectedSprite;
	sf::Sprite save2SelectedSprite;
	sf::Sprite save3SelectedSprite;

	sf::Sprite resumeGameSprite;
	sf::Sprite resumeGameSelectedSprite;
	sf::Sprite saveGameSprite;
	sf::Sprite saveGameSelectedSprite;
	sf::Sprite mainMenuSprite;
	sf::Sprite mainMenuSelectedSprite;
	sf::Sprite exitGameSprite;
	sf::Sprite exitGameSelectedSprite;*/


	/***********************
	* Variables for Background
	**********************/

	sf::Texture* Junglebackground1 = nullptr;
	sf::Texture* Cavebackground1 = nullptr;
	sf::Texture* Treebackground1 = nullptr;
	sf::Texture* Hud = nullptr;

	sf::Sprite Junglebackground1Sprite;
	sf::Sprite Junglebackground6Sprite;
	sf::Sprite Cavebackground1Sprite;
	sf::Sprite Cavebackground2Sprite;
	sf::Sprite Cavebackground3Sprite;
	sf::Sprite Treebackground1Sprite;
	sf::Sprite HudSprite;

	/**********************/


	const int ArraySize = 1000;
	int** collidableArray;
	int** interactionArray;

	//Dependensies
	Player* player;

	//PrincessObject* princess;

	//Mace* mace;

	//std::vector<AIEnemies*>* AIVectorPointer = &AIVector;
	//std::vector<AIEnemies*> AIVector;

	Config* config;
	std::list<Object*> objects;
	//std::list<Teleport*> teleports;
	std::map<int, Object*> teleports;
	std::list<SpawnPoint*> spawnpointList;
	sf::Clock* clock;
	sf::RenderWindow* window;

	// Stuff for timer
	sf::Clock* timer;
	sf::Text* timerInText;
	sf::Font* font;
	int timerX;
	int timerY;
	int penaltyTime = 0;
	int EscMenuTime = 0;
	int fps = 0;
	float fpsBeforeRender = 0.00;
	float fpsAfterRender = 0.00;
	float fpsDelta = 0.00;

	//Bonus Score
	int monkeykill = 0;


	// Clock for DialogDuration
	sf::Clock* DialogueDuration;
	sf::View* currentView;
	//Camera camera;
	/*Music* music;
	Sounds* sound;
	Dialogue dialogue;*/
};


#endif