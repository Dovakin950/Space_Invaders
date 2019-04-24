#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Alien {
public:
	Alien();
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture textureDeath;
	sf::Sprite sprite;
	//sf::RectangleShape sprite;
	const int width = 60;
	const int height = 60;
	float x = 0, y = 0;
	bool display = true;
	bool front = false;
	bool spriteDeath = false;
	void CheckDeath(Bullet bullets[50]);
	void death();
};