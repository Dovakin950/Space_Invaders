#include "Game.h"
#include <iostream>

Game::Game() :myWindow(sf::VideoMode(800, 680), "SFML Game") {
	wasted.loadFromFile("loose.png");
	loose.setTexture(wasted);
	loose.setPosition(sf::Vector2f(150,150));
	restart.loadFromFile("restart.png");
	restartBtn.setTexture(restart);
	restartBtn.setPosition(sf::Vector2f(300, 312));
	Pause_texture.loadFromFile("Pause.png");
	Pause_sprite.setTexture(Pause_texture);
	Pause_sprite.setPosition(sf::Vector2f(150, 150));
	Continue_Btn_texture.loadFromFile("Continue.png");
	Continue_Btn_sprite.setTexture(Continue_Btn_texture);
	Continue_Btn_sprite.setPosition(sf::Vector2f(200,301));
	Win_texture.loadFromFile("Win.png");
	Win_sprite.setTexture(Win_texture);
	Win_sprite.setPosition(sf::Vector2f(290, 72));
	heartTexture.loadFromFile("heart.png");
	Wall_textures[0].loadFromFile("wall1.png");
	Wall_textures[1].loadFromFile("wall2.png");
	Wall_textures[2].loadFromFile("wall3.png");
	Wall_textures[3].loadFromFile("wall4.png");
	for (int i = 0; i < 5; i++)
		heartSprites[i].setTexture(heartTexture);
	for (int i = 0; i < 5; i++)
	{
		heartSprites[i].setPosition(sf::Vector2f(255+i*60,610));
	}
	BottomBorder.setSize(sf::Vector2f(800, 10));
	BottomBorder.setPosition(sf::Vector2f(0, 600));
	BottomBorder.setFillColor(sf::Color::Red);
}
void Game::AliensInit() {
	Aliens_Dead = 0;
	int offsetX = 160;
	for (int i = 0; i < AlienRows; i++) {
		aliens[i][0].display = true;
		aliens[i][0].front = false;
		aliens[i][0].x = offsetX;
		aliens[i][0].y = (aliens[i][0].height + AlienMarginY)*i;
		aliens[i][0].sprite.setPosition(sf::Vector2f(aliens[i][0].x, aliens[i][0].y));
		for (int j = 1; j < AlienColumns; j++) {
			aliens[i][j].display = true;
			aliens[i][j].front = false;
			aliens[i][j].x = aliens[i][j - 1].x + aliens[i][j - 1].width + AlienMarginX;
			aliens[i][j].y = aliens[i][j - 1].y;
			aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
		}
	}
	for (int j = 0; j < AlienColumns; j++)
		aliens[AlienRows-1][j].front = true;
	alienDir = Dir(RIGHT);
}
void Game::AliensCheckDeath() {
	for (int k = 0; k < 50; k++)
	{
		if (bullet[k].display) {
			for (int i = 0; i < AlienRows; i++)
				for (int j = 0; j < AlienColumns; j++)
				{
					if (aliens[i][j].front) {
						if (((bullet[k].x >= aliens[i][j].x && bullet[k].x <= aliens[i][j].x + aliens[i][j].width) && (bullet[k].y <= aliens[i][j].y + aliens[i][j].height)) || ((bullet[k].x + bullet[k].width >= aliens[i][j].x && bullet[k].x + bullet[k].width <= aliens[i][j].x + aliens[i][j].width) && (bullet[k].y <= aliens[i][j].y + aliens[i][j].height))) {
							bullet[k].display = false;
							aliens[i][j].death();
							Aliens_Dead++;
							AlienDeathAnimClock.restart();
							if (i > 0) aliens[i-1][j].front = true;
							break;
						}
					}
				}
		}
	}
}
void Game::AliensShoot() {
	//std::cout << 1 << "\n";
	for (int i = 0; i < AlienRows; i++)
		for (int j = 0; j < AlienColumns; j++)
			if (aliens[i][j].front && (aliens[i][j].x + aliens[i][j].width / 2 >= player.x) && (aliens[i][j].x <= player.x + player.width)) {
				int k = 0;
				while (bullet[k].display == true) k++;
				bullet[k].x = (aliens[i][j].x + aliens[i][j].width / 2)-bullet[k].width/2;
				bullet[k].y = aliens[i][j].y + aliens[i][j].height;
				bullet[k].sprite.setPosition(sf::Vector2f(bullet[k].x, bullet[k].y));
				bullet[k].yspeed = 0.1;
				//std::cout << "yspeed " << bullet[k].yspeed << "\n";
				bullet[k].display = true;
				bullet[k].update();
				break;
			}
}
void Game::AliensMove() {
	int xspeed, yspeed;
	static bool NextMoveRight = false;
	bool Collision = false;
	switch (alienDir) {
	case RIGHT:
		for (int i = 0; i < AlienRows; i++)
		{
			xspeed = 40;
			yspeed = 40;
			int j = AlienColumns - 1;
			while (!aliens[i][j].display) j--;
			aliens[i][j].x += xspeed;
			aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
			if (aliens[i][j].x + aliens[i][j].width >= 800) {
				xspeed = (aliens[i][j].x + aliens[i][j].width) - 800;
				aliens[i][j].x = 800 - aliens[i][j].width;
				aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
				alienDir = Dir(DOWN);
				NextMoveRight = false;
			}
			j--;
			for (j; j >= 0; j--)
				if (aliens[i][j].display) {
					aliens[i][j].x += xspeed;
					aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
				}
		}
		break;
	case LEFT:
		for (int i = 0; i < AlienRows; i++)
		{
			xspeed = 40;
			yspeed = 40;
			int j = 0;
			while (!aliens[i][j].display) j++;
			aliens[i][j].x -= xspeed;
			aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
			if (aliens[i][j].x <= 0) {
				xspeed +=aliens[i][j].x;
				aliens[i][j].x = 0;
				aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
				alienDir = Dir(DOWN);
				NextMoveRight = true;
			}
			j++;
				for (j; j < AlienColumns; j++)
					if (aliens[i][j].display) {
						aliens[i][j].x -= xspeed;
						aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
					}
		}
		break;
	case DOWN:
		for (int j = 0; j < AlienColumns; j++)
		{
			xspeed = 40;
			yspeed = 40;
			int i = AlienRows - 1;
			while (!aliens[i][j].display) i--;
			aliens[i][j].y += yspeed;
			aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
			i--;
			for (i; i >= 0; i--)
			{
				if (aliens[i][j].display) {
					aliens[i][j].y += yspeed;
					aliens[i][j].sprite.setPosition(sf::Vector2f(aliens[i][j].x, aliens[i][j].y));
				}
			}
			if (NextMoveRight) alienDir = Dir(RIGHT);
			else alienDir = Dir(LEFT);
		}
		break;
	}
}

void Game::AliensAnim() {
	sf::Time time;
	time = AlienAnimClock.getElapsedTime();
	if (time.asSeconds() >= 1.f) {
		AlienSprite1 = !AlienSprite1;
		AlienAnimClock.restart();
	}
	for (int i = 0; i < AlienRows; i++) 
		for (int j = 0; j < AlienColumns; j++){
			if (aliens[i][j].spriteDeath) {
				aliens[i][j].sprite.setTexture(aliens[i][j].textureDeath); 
			}
			else if (AlienSprite1) aliens[i][j].sprite.setTexture(aliens[i][j].texture1);
					else aliens[i][j].sprite.setTexture(aliens[i][j].texture2);
	}
			
}
void Game::WallsInit() {
	int MarginX = 88;
	int MarginY = player.height + 40 + 20;
	/*walls[0].display = true;
	walls[0].Break_Point = 0;
	walls[0].sprite.setTexture(Wall_textures[0]);
	walls[0].x = MarginX;
	walls[0].y = 600-MarginY;
	walls[0].sprite.setPosition(sf::Vector2f(walls[0].x, walls[0].y));*/
	for (int i = 0; i < 4; i++)
	{
		walls[i].display = true;
		walls[i].Break_Point = 0;
		walls[i].sprite.setTexture(Wall_textures[0]);
		walls[i].x = MarginX+i*(walls[i].width+MarginX);
		//walls[i].x = walls[i - 1].x + walls[i - 1].width + MarginX;
		walls[i].y = 600-MarginY;
		walls[i].sprite.setPosition(sf::Vector2f(walls[i].x, walls[i].y));
	}
}
void Game::WallsCheckCollision() {
	for (int i = 0; i < 4; i++)
	{
		if (walls[i].display)
			for (int k = 0; k < 50; k++)
			{
				if (bullet[k].display && (bullet[k].x >= walls[i].x && bullet[k].x <= walls[i].x + walls[i].width) && (bullet[k].y <= walls[i].y + walls[i].height && bullet[k].y >= walls[i].y)) {
					if (bullet[k].yspeed > 0) {
						bullet[k].display = false;
						bullet[k].yspeed*=-1;
						walls[i].hit(Wall_textures);
					}
					else {
						bullet[k].display = false;
						walls[i].hit(Wall_textures);
					}
				}
			}
	}
}
void Game::PlayerCheckHit() {
	for (int i = 0; i < 50; i++)
	{
		if ((bullet[i].display && (bullet[i].x >= player.x && bullet[i].x <= player.x + player.width) && (bullet[i].y + bullet[i].height >= player.y))) {
			bullet[i].display = false;
			bullet[i].x = 0;
			bullet[i].y = 0;
			bullet[i].yspeed *= -1;
			player.HP--;
			std::cout << player.HP << "\n";
			break;
		}
	}
}
void Game::GameCheckLoose() {
	if (player.HP == 0)
		Game_State = LOOSE;
}
void Game::GameCheckWin() {
	if (Aliens_Dead == 18)
		Game_State = WIN;
}
void Game::CheckRestart() {
	restartBtn.setColor(sf::Color::White);
	if (sf::IntRect(300, 312, 500, 512).contains(sf::Mouse::getPosition(myWindow))) {
		restartBtn.setColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			GameRestart();
		}
	}
}
void Game::GameRestart() {
	AliensInit();
	for (int i = 0; i < 50; i++)
	{
		bullet[i].display = false;

	}
	WallsInit();
	player.HP = 5;
	player.sprite.setPosition(sf::Vector2f(350,550));
	Game_State = PLAYING;
}
void Game::CheckContinue() {
	Continue_Btn_sprite.setColor(sf::Color::White);
	if (sf::IntRect(200, 301, 600, 411).contains(sf::Mouse::getPosition(myWindow))) {
		Continue_Btn_sprite.setColor(sf::Color::Green);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			Game_State = PLAYING;
		}
	}
}
void Game::run()
{
	AliensInit();
	WallsInit();
	while (myWindow.isOpen())
	{
		switch (Game_State)
		{
		case PLAYING:
			ProcessEvents();
			update();
			render();
			break;
		case PAUSE:
			myWindow.clear();
			myWindow.draw(Pause_sprite);
			myWindow.draw(Continue_Btn_sprite);
			myWindow.display();
			CheckContinue();
			break;
		case LOOSE:
			myWindow.clear();
			myWindow.draw(loose);
			myWindow.draw(restartBtn);
			myWindow.display();
			CheckRestart();
			break;
		case WIN:
			myWindow.clear();
			myWindow.draw(Win_sprite);
			myWindow.draw(restartBtn);
			myWindow.display();
			CheckRestart();
			break;
		}
	}
}
void Game::ProcessEvents()
{
	sf::Event event;
	while (myWindow.pollEvent(event) && player.HP != 0)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed: handlePlayerInput(event.key.code, true); break;
		case sf::Event::KeyReleased: handlePlayerInput(event.key.code, false); break;
		case sf::Event::Closed: myWindow.close(); break;
		}
	}
	
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::A) player.movingLeft = isPressed;
	if (key == sf::Keyboard::D) player.movingRight = isPressed;
	if (key == sf::Keyboard::Space && isPressed && !shoot) {
		shoot = true; 
		player.Shoot(bullet); 
	} 
	else 
		if (key == sf::Keyboard::Space && !isPressed) {
		shoot = false;
	}
	if (key == sf::Keyboard::Escape) Game_State = PAUSE;
}

void Game::update()
{
	sf::Time time;
	player.update();
	for (int i = 0; i < 50; i++)
		if (bullet[i].display) {
			bullet[i].update();
			//std::cout << 1 << "\n";
		}
	time = ShootClock.getElapsedTime();
	if (time.asSeconds() >= 1) {
		AliensShoot();
		ShootClock.restart();
	}
	AliensCheckDeath();
	AliensAnim();
	if (MoveClock.getElapsedTime().asSeconds() >= 2) {
		MoveClock.restart();
		AliensMove();
	}
	WallsCheckCollision();
	PlayerCheckHit();
	GameCheckLoose();
	GameCheckWin();
}

void Game::render()
{
	sf::Time time;
	myWindow.clear();
	myWindow.draw(player.sprite);
	for (int i = 0; i < 50; i++) {
		if (bullet[i].display) myWindow.draw(bullet[i].sprite);
	}
	time = AlienDeathAnimClock.getElapsedTime();
	for (int i = 0; i < AlienRows; i++)
		for(int j=0;j< AlienColumns;j++)
			if(aliens[i][j].display)
				if (aliens[i][j].spriteDeath && time.asMilliseconds()>=500) {
					aliens[i][j].spriteDeath = false;
					aliens[i][j].display = false;
					myWindow.draw(aliens[i][j].sprite);
				}
				else myWindow.draw(aliens[i][j].sprite);
	for (int i = 0; i < 4; i++)
		if(walls[i].display)
		myWindow.draw(walls[i].sprite);
	myWindow.draw(BottomBorder);
	for (int i = 0; i < player.HP; i++)
		myWindow.draw(heartSprites[i]);
	myWindow.display();
}
