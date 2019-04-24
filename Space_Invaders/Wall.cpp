#include "Wall.h"
#include <SFML/Graphics.hpp>
Wall::Wall() {
	width =90;
	height = 39;
}
void Wall::hit(sf::Texture* textures) {
	Break_Point++;
	if (Break_Point == 4) display = false;
	else
	sprite.setTexture(textures[Break_Point]);
}