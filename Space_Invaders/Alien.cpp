#include <SFML/Graphics.hpp>
#include "Alien.h"
#include <iostream>
Alien::Alien(){
	texture1.loadFromFile("alien1.png");
	texture2.loadFromFile("alien2.png");
	textureDeath.loadFromFile("alien3.png");
	sprite.setTexture(texture1);
	//sprite.setSize(sf::Vector2f(width, height));
	//sprite.setFillColor(sf::Color::Red);
}
void Alien::CheckDeath(Bullet bullet[50]) {
	for(int i=0;i<50;i++)
		if(bullet[i].display){
			if ((bullet[i].x>= Alien::x && bullet[i].x <= Alien::x + Alien::width) && (bullet[i].y <= Alien::y)) {
				Alien::death();
				bullet[i].display = false;
				break;
			}
		}
}
void Alien::death() {
	//std::cout << 1 << "\n";
	Alien::spriteDeath = true;
	Alien::front = false;
}