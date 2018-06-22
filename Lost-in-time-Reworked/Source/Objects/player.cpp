#include "player.h"
#include <iostream>
#include <stdlib.h>

Player::Player(float x, float y, sf::RenderWindow* window) : window(window)
{
	this->posX = x;
	this->posY = y;
	this->OriginalX = x;
	this->OriginalY = y;
	character = new sf::RectangleShape;
	character->setSize(sf::Vector2f(sizeWidth, sizeHeight));

	animation.init();
	animation.PlayerIdle(character);

	/*
	health.init();
	health.SetOriginalLifePoints(100);
	health.SetActualLifePoints(100);
	health.SetVisibleLifePoints(100);

	sound = new Sounds();*/
}


Player::~Player()
{
}


float Player::GetOriginalX()
{
	return OriginalX;
}

float Player::GetOriginalY()
{
	return OriginalY;
}

void Player::SetOriginalX(float x)
{
	this->OriginalX = x;
}

void Player::SetOriginalY(float y)
{
	this->OriginalY = y;
}

void Player::Reset2OriginalX(float x)
{
	x = this->OriginalX;
}

void Player::Reset2OriginalY(float y)
{
	y = this->OriginalY;
}
/**
* Cutscene animation for player facing left.
* @param delta
*/
void Player::PlayerCutsceneAnimationLeft(float delta)
{
	counter += delta;
	if (counter >= 0.1)
	{
		counter = 0;
		animation.PlayerIdleLeft(character);
	}
}
/**
* Cutscene animation for player facing right.
* @param delta
*/

void Player::PlayerCutsceneAnimationRight(float delta)
{
	counter += delta;
	if (counter >= 0.1)
	{
		counter = 0;
		animation.PlayerIdle(character);
	}
}


/**
* The function that is responsible to call each of
* the player character's animations. All animations switch
* frames based on a delta timer.
* @param delta
*/
void Player::PlayerAnimation(float delta, bool attack)
{
	counter += delta;
	if (counter >= 0.15)
	{
		if (attack)
			animation.PlayerAttackRight(character);
		counter = 0;
		if (jumpcheck && movedirection == 1) // If jumping to the right
		{
			animation.PlayerJumpRight(character, apexcheck);
			lastmovedirection = 1;
		}
		else if (jumpcheck && movedirection == 0) // If jumping to the left
		{
			animation.PlayerJumpLeft(character, apexcheck);
			lastmovedirection = 0;
		}
		else if (jumpcheck) //If jumping upwards.
		{
			if (lastmovedirection == 1)
				animation.PlayerJumpRight(character, apexcheck);
			else
				animation.PlayerJumpLeft(character, apexcheck);
		}

		else
		{
			if (movedirection == 0) // If moving to left, play left animation
			{
				animation.PlayerWalkLeft(character);
			}
			if (movedirection == 1) // If moving to right, play right animation
			{
				animation.PlayerWalkRight(character);
			}
			if (movedirection == 2) // If movement stopped, play idle animation
			{
				if (lastmovedirection == 0)
					animation.PlayerIdleLeft(character);
				else
					animation.PlayerIdle(character);
			}
		}
	}
}

/**
* The sound to be played when the player character jumps.
*/
void Player::PlayerSoundJump()
{
	//sound->playSound("/Jump.wav", 100);
}
/**
* The sounds to be played if the player character were to be harmed.
* There is about 50% for each of the sounds to be played.
*/
void Player::PlayerSoundHurt()
{/*
	if (rand() % 20 < 10)
		sound->playSound("/manhurt1.wav", 100);
	else
		sound->playSound("/manhurt2.wav", 100);*/
}

/**
* The sound to be played if the player character were to
* succeed on harming an enemy by jumping on it.
*/
void Player::PlayerSoundEnemyLanded()
{
	//sound->playSound("/jumpedonenemy.wav", 100);
}


/**
* When player is dead this function is called.
* Reset variables that need reseted.
* Call to health reset function.
* Set player position back to spawn position.
* TODO: Draw deathscreen, atm: print out deathmessage
*/
void Player::PlayerDead()
{
	this->jumpcheck = true;
	this->apexcheck = true;
	jumpspeed = origjumpspeed;
	fallspeed = 0;
	movedirection = 2;
	movespeedleft = 0;
	movespeedright = 0;
	this->positionX = OriginalX;
	this->positionY = OriginalY;
	//sound->playSound("/Death.wav", 100);
}

/**
* Set the position for the character at PositionX and Y
* Draw the character to the window.
*/
void Player::DrawMe()
{
	// Position the rectangle used to draw the square
	character->setPosition(posX, posY);

	// Draw the square
	window->draw(*character);
}