#pragma once
#include <SFML/Graphics.hpp>
class Bullet {
public:
	Bullet();
	void update();
public:
	sf::RectangleShape sprite;
	float x = 0, y = 0;
	const int width = 5;
	const int height = 20;
	bool display = false;
	float yspeed = -0.1;
};