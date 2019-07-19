#include "pch.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
#include <string>
#include <random>
#include <SFML/Audio.hpp>


int main()
{
	RenderWindow window(VideoMode(850, 750), "SFML"); //canvas

	//player
	Sprite player;
	Texture playerLeftTexture;
	playerLeftTexture.loadFromFile("Texture/cavemanleft.png");
	Texture playerRightTexture;
	playerRightTexture.loadFromFile("Texture/cavemanright.png");
	player.setTexture(playerLeftTexture);
	player.setScale(0.5, 0.5);
	player.setPosition(350, 350);

	//player feet collider
	RectangleShape feet;
	feet.setSize(Vector2f(45, 1));
	feet.setPosition(player.getPosition().x + 30, player.getPosition().y);
	feet.setFillColor(Color::Transparent);

	//player head collider
	RectangleShape head;
	head.setSize(Vector2f(40, 1));
	head.setPosition(player.getPosition().x + 30, player.getPosition().y);
	head.setFillColor(Color::Transparent);

	//score
	Text text;
	Font myFont;
	myFont.loadFromFile("Font/Muli-Black.ttf");
	text.setFont(myFont);
	text.setCharacterSize(24);
	text.setPosition(650, 100);
	text.setFillColor(Color::White);
	text.setString("Score");

	//music
	Music music;
	music.openFromFile("Music/pixelmusic.wav");
	music.setLoop(true);
	music.play();
	music.setVolume(100);

	//gameover music
	Music gameOverMusic;
	gameOverMusic.openFromFile("Music/gameover.wav");
	gameOverMusic.play();
	gameOverMusic.setLoop(true);
	gameOverMusic.setVolume(0);

	//ground
	Sprite ground;
	Texture groundTexture;
	groundTexture.loadFromFile("Texture/platform.png");
	ground.setScale(4.9,4);
	ground.setTexture(groundTexture);
	ground.setPosition(-5, 600);

	//rock
	Sprite rock;
	Texture rockTexture;
	rockTexture.loadFromFile("Texture/rock .png");
	rock.setTexture(rockTexture);
	rock.setScale(0.25, 0.25);
	rock.setPosition(400, -2);

	//bat
	Sprite bat;
	Texture batTexture;
	batTexture.loadFromFile("Texture/bat.png");
	bat.setTexture(batTexture);
	bat.setScale(0.5, 0.5);
	bat.setPosition(200, 200);

	//background
	Sprite background;
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("Texture/cavebackground.png");
	background.setTexture(backgroundTexture);
	background.setPosition(0, 0);
	
	//platform1
	Sprite platform1;
	Texture platform1Texture;
	platform1Texture.loadFromFile("Texture/platform.png");
	platform1.setTexture(platform1Texture);
	platform1.setPosition(20, 220);
	platform1.setScale(1.7, 2);

	//top of platform1
	RectangleShape platform1Top;
	platform1Top.setFillColor(Color::Transparent);
	platform1Top.setSize(Vector2f(299,5));
	platform1Top.setPosition(platform1.getPosition().x + 2, platform1.getPosition().y + 2);

	//bottom of platform1
	RectangleShape platform1Bottom;
	platform1Bottom.setFillColor(Color::Transparent);
	platform1Bottom.setSize(Vector2f(299, 5));
	platform1Bottom.setPosition(platform1.getPosition().x + 2, platform1.getPosition().y + 75);

	//platform2
	Sprite platform2;
	Texture platform2Texture;
	platform2Texture.loadFromFile("Texture/platform.png");
	platform2.setTexture(platform2Texture);
	platform2.setPosition(500, 400);
	platform2.setScale(1.7, 2);

	//top of platform2
	RectangleShape platform2Top;
	platform2Top.setFillColor(Color::Transparent);
	platform2Top.setSize(Vector2f(299, 5));
	platform2Top.setPosition(platform2.getPosition().x + 2, platform2.getPosition().y + 2);

	//bottom of platform2
	RectangleShape platform2Bottom;
	platform2Bottom.setFillColor(Color::Transparent);
	platform2Bottom.setSize(Vector2f(299, 5));
	platform2Bottom.setPosition(platform2.getPosition().x + 2, platform2.getPosition().y + 75);

	//gameover
	Sprite gameoverScreen;
	Texture gameoverTexture;
	gameoverTexture.loadFromFile("Texture/gameover.png");
	gameoverScreen.setTexture(gameoverTexture);
	gameoverScreen.setPosition(110, 80);

	//gameoverScore
	Text gameOverScore;
	gameOverScore.setFont(myFont);
	gameOverScore.setCharacterSize(24);
	gameOverScore.setFillColor(Color::White);
	gameOverScore.setPosition(300, 470);


	//time
	Clock clock;
	float timer;
	bool stopTime = false;
	int speedIncrement1 = 1;
	int speedIncrement2 = 1;
	float batSpeed = -0.2f;
	float rockSpeed = 0.2f;
	bool left = false;
	bool right = false;
	bool jumping = false;
	bool gravity = true;
	bool grounded = false;
	bool gameover = false;

	Vector2f playerPosBeforeJump;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code ==Keyboard::Escape)
					window.close();



				if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left) {
					left = true;
					player.setTexture(playerLeftTexture);
				}

				if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right) {
					right = true;
					player.setTexture(playerRightTexture);
				}

				//if ((event.key.code == Keyboard::Space && player.getPosition().y == 470) || (event.key.code == Keyboard::Space && player.getPosition().y == 262) || (event.key.code == Keyboard::Space && player.getPosition().y == 82)) {
				//	jumping = true;
				//}

				if (jumping == false && grounded == true) {
					if(event.key.code == Keyboard::Space){
					jumping = true;
					grounded = false;
					playerPosBeforeJump = player.getPosition();
					}
				}

			}

			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::A || event.key.code == Keyboard::Left) {
					left = false;
				}

				if (event.key.code == Keyboard::D || event.key.code == Keyboard::Right) {
					right = false;
				}

				
			}


		}

		//time code
		if (stopTime == false) {
			timer = clock.getElapsedTime().asSeconds();

			if (timer > 1.f) {
				text.setString(std::to_string (timer));
				gameOverScore.setString("Time: " + std::to_string(timer));
			}
		}




		head.setPosition(player.getPosition().x + 30, player.getPosition().y); //head collider position
		feet.setPosition(player.getPosition().x + 30, player.getPosition().y + 139); //feet collider position

		if (head.getGlobalBounds().intersects(platform1Bottom.getGlobalBounds()) || head.getGlobalBounds().intersects(platform2Bottom.getGlobalBounds())) {
			jumping = false;

		}

		if (feet.getGlobalBounds().intersects(platform1Top.getGlobalBounds())) {
			player.setPosition(player.getPosition().x, 82);
			//jumping = false;
			grounded = true;
		}

		if (feet.getGlobalBounds().intersects(platform2Top.getGlobalBounds())) {
			player.setPosition(player.getPosition().x, 262);
			//jumping = false;
			grounded = true;
		}



		Vector2f movement(0, 0);
		if (left)
			movement.x -= 0.3f;
		if (right)
			movement.x = 0.3f;

		if (jumping == true) {
			if (player.getPosition().y > (playerPosBeforeJump.y - 240)) { //limits jump height
				movement.y -= 0.7f;
			}

			else {
				jumping = false;
			}
		}

		player.move(movement);
		player.move(0, 0.2f);
		bat.move(batSpeed, 0);
		rock.move(0, rockSpeed);


		random_device rd;
		int batnum = rd() % 5;
		int rocknum = rd() % 7;
		float randY;
		float randX;

		switch (batnum) {
		case 0:
			randY = 100;
			break;

		case 1:
			randY = 430;
			break;

		case 2:
			randY = 220;
			break;

		case 3:
			randY = 500;
			break;

		default:
			randY = 300;

		}

		switch (rocknum) {
		case 0:
			randX = 100;
			break;
		case 1:
			randX = 230;
			break;
		case 2:
			randX = 350;
			break;
		case 3:
			randX = 410;
			break;
		case 4:
			randX = 500;
			break;

		case 5:
			randX = 630;
			break;
		default:
			randX = 740;
		}

		if (player.getPosition().y > 470)
		{
			player.setPosition(player.getPosition().x, 470);
			//jumping = false;
			grounded = true;
		}

		if (player.getPosition().x < -80) {
			player.setPosition(880, player.getPosition().y);
		}

		if (player.getPosition().x > 920) {
			player.setPosition(-40, player.getPosition().y);
		}

		if (rock.getPosition().y > 790) {
			rock.setPosition(randX, -2);
			speedIncrement1++;
		}

		if (bat.getPosition().x < -120) {
			bat.setPosition(880, randY);
			speedIncrement2++;
		}

		if (player.getGlobalBounds().intersects(bat.getGlobalBounds())) {
			gameover = true;
			stopTime = true;
		}

		if (player.getGlobalBounds().intersects(rock.getGlobalBounds())) {
			gameover = true;
			stopTime = true;
		}


		if (speedIncrement1 % 5 == 0) { //every 5 times the rock gets past the point where it sets the rock back it speeds up
			batSpeed -= 0.0001;
		}

		if (speedIncrement2 % 5 == 0) { //every 5 times the rock gets past the point where it sets the rock back it speeds up
			rockSpeed += 0.0001;
		}

		window.clear();
		if(gameover == false){ //edit this 
		window.draw(background);
		window.draw(player);
		window.draw(feet);
		window.draw(head);
		window.draw(platform1);
		window.draw(platform2);
		window.draw(platform1Top);
		window.draw(platform2Top);
		window.draw(platform1Bottom);
		window.draw(platform2Bottom);
		window.draw(text);
		window.draw(rock);
		window.draw(bat);
		window.draw(ground);
		}

		else {
			music.setVolume(0);
			gameOverMusic.setVolume(100);
			window.draw(gameoverScreen);
			window.draw(gameOverScore);
		}
		window.display();
	}
}