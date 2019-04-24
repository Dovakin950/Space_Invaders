#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Alien.h"
#include"Wall.h"
enum Dir {
	RIGHT,
	LEFT,
	DOWN
};
enum Game_state {
	PLAYING,
	PAUSE,
	LOOSE,
	WIN
};
class Game
{
public:
	Game();
	void run();
private:
	Game_state Game_State=PLAYING;
	const int AlienRows = 3, AlienColumns = 6;
	Alien aliens[3][6];
	int AlienMarginX = 20, AlienMarginY = 10;
	int Aliens_Dead = 0;
	sf::RenderWindow myWindow;
	Player player;
	Bullet bullet[50];
	sf::Clock ShootClock;
	sf::Clock MoveClock;
	sf::Clock AlienAnimClock;
	sf::Clock AlienDeathAnimClock;
	bool shoot = false;
	bool AlienSprite1 = true;
	bool GameLoose = false;
	Wall walls[4];
	sf::Texture Wall_textures[4];
	Dir alienDir = Dir(RIGHT);
	sf::Texture wasted,restart;
	sf::Sprite loose,restartBtn;
	sf::Texture Pause_texture;
	sf::Sprite Pause_sprite;
	sf::Texture Continue_Btn_texture;
	sf::Sprite Continue_Btn_sprite;
	sf::Texture Win_texture;
	sf::Sprite Win_sprite;
	sf::RectangleShape BottomBorder;
	sf::Texture heartTexture;
	sf::Sprite heartSprites[5];
	private:
	void ProcessEvents();
	void update();
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void AliensInit();
	void AliensShoot();
	void AliensCheckDeath();
	void AliensMove();
	void AliensAnim();
	void WallsInit();
	void WallsCheckCollision();
	void PlayerCheckHit();
	void GameCheckLoose();
	void GameCheckWin();
	void CheckRestart();
	void GameRestart();
	void CheckContinue();
};