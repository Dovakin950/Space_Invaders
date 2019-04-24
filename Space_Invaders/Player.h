#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Player {
public:
	Player();
	void update();
public:
	bool movingLeft = false, movingRight = false;
	float x = 350;
	int width = 70, height = 40;
	const float y = 550.f;
	int HP = 5;
	//sf::RectangleShape sprite;
	//int ID;
	//int score;
	sf::Texture texture;
	sf::Sprite sprite;
	//Bullet bullet[50];
	void Shoot(Bullet bullet[50]);
private:
	void move(float dir);
private:
	float xspeed = 0.1;
	
};