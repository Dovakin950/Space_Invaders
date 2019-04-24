#include <SFML/Graphics.hpp>
#include "Player.h"
#include<iostream>
Player::Player() :sprite() {
	//sprite.setFillColor(sf::Color::Cyan);
	//sprite.setSize(sf::Vector2f(width, height));
	HP = 5;
	texture.loadFromFile("ship.png");
	sprite.setTexture(texture);
	sprite.setPosition(x, y);
}
void Player::move(float dir) {
	x += dir * xspeed;
	sprite.setPosition(sf::Vector2f(x, y));
	if (x <= 0) {
		x = 0;
		sprite.setPosition(sf::Vector2f(x, Player::y));
	}
	else if (x + width >= 800) {
		x = 800 - width;
		sprite.setPosition(sf::Vector2f(x, y));
	}
}
void Player::Shoot(Bullet bullet[50]) {
	int i = 0;
	while (bullet[i].display == true) i++;
	bullet[i].x = Player::x + Player::width / 2.f - bullet[i].width / 2.f;
	bullet[i].y = Player::y - bullet[i].height-10;
	bullet[i].sprite.setPosition(sf::Vector2f(bullet[i].x, bullet[i].y));
	bullet[i].display = true;
	bullet[i].update();
}
//sf::Vector2f(Player::sprite.getSize().x / 2.f - bullet.width / 2.f, Player::y + bullet.height)
void Player::update() {
	if (movingLeft){
		move(-1.f);
	}
	else if (movingRight) {
		move(1.f);
	}
}