#pragma once
#include <SFML/Graphics.hpp>
class Wall {
public:
	int x, y, width, height;
	sf::Sprite sprite;
	int Break_Point = 0;
	bool display = true;
	Wall();
	void hit(sf::Texture* textures);
};