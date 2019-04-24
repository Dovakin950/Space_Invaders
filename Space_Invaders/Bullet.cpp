#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
Bullet::Bullet(){
	Bullet::display = false;
	sprite.setFillColor(sf::Color::Green);
	sprite.setSize(sf::Vector2f(Bullet::width, Bullet::height));
}
void Bullet::update() {
	if (Bullet::display) {
		Bullet::y += Bullet::yspeed;
		Bullet::sprite.setPosition(sf::Vector2f(Bullet::x,Bullet::y));
	}
	if (Bullet::y + Bullet::height <= 0) {
		Bullet::display = false;
		Bullet::yspeed = -0.1;
	}
	else if(Bullet::y + Bullet::height >= 600) {
		Bullet::display = false;
		Bullet::yspeed = -0.1;
	}
}

	