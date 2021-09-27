#include <iostream>
#include <random>
#include <string>
#include <SFML\Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Ghost.h"

int main() {

	/*
	- To move the player use the arrow keys up, down, left and right.
	- When the player & the ghost crosses paths the window will terminate inidcating it game over.
	- The score is recorded both on the terminal and windows.
	- The window shows instructions. 

		* indicating how the game will be played.
		* The score during playe mode.
		* And the how to exit the game when it complete.

	 - Because the ghosts are using one member of class Ghost, player and ghost collision is imidiately detected.
	*/

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(2.5f / 60.f);
	int score = 0;

	sf::RenderWindow window(sf::VideoMode(1900,900), "Pacman: Sizwe Nkosi");

	Map map("Files/map.txt");

	Player player = Player(&map, "Files/pacman.png", sf::Vector2f(200, 232));

	Ghost ghost = Ghost(&map, "Files/ghost.png", sf::Vector2f(200, 88));
	Ghost ghost2 = Ghost(&map, "Files/ghost2.png", sf::Vector2f(200, 88));
	Ghost ghost3 = Ghost(&map, "Files/ghost3.png", sf::Vector2f(200, 88));
	Ghost ghost4 = Ghost(&map, "Files/ghost4.png", sf::Vector2f(200, 88));

	sf::Font font;
	if (!font.loadFromFile("Files/font.ttf")){
		std::cout <<"\nERROR::failed to load font" <<std::endl;
		exit(0);
	}

	sf::Text text;
	text.setFont(font);
	text.setPosition(sf::Vector2f(500, 100));
	text.setCharacterSize(256);
	text.setFillColor(sf::Color::White);

	sf::Event event;

	while (window.isOpen()) {

		score = player.getScore();
		if( score < 1){
		text.setCharacterSize(60);
		text.setString("To play use the arrow 'KEYS':\n \n- UP, Down, left and Right.\n \n- The the Ghost cannot be frigten.\n \n- If the PLAYER dies, the window terminates.\n \n- To exit press 'Esc'");
		}

		else if(score > 83){
			text.setCharacterSize(100);
			text.setString("GAME FINISHED SCORE : 84\n \nPRESS 'Esc'.");
		}
		else{
		text.setCharacterSize(100);
		std::string sc = std::to_string(score);
		text.setString("Score : " + sc +"\nPress 'Esc' to exit");
		}

		while (window.pollEvent(event)) {
			switch (event.type) {
				
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if(event.key.code == sf::Keyboard::Escape){
					window.close();
				}else{
				switch (event.key.code) {
				}
				}
				break;
			}
		}

		while (accumulator > ups) {
			accumulator -= ups;
			player.updateLogic(ghost.getPos());
			player.updateLogic(ghost2.getPos());
			player.updateLogic(ghost3.getPos());
			player.updateLogic(ghost4.getPos());

			ghost.updateLogic();
			ghost2.updateLogic();
			ghost3.updateLogic();
			ghost4.updateLogic();
		}

		window.clear();
		
		map.draw(&window);
		player.draw(&window);

		ghost.draw(&window);
		ghost2.draw(&window);
		ghost3.draw(&window);
		ghost4.draw(&window);

		window.draw(text);
		window.display();
		accumulator += clock.restart();
	}
	return EXIT_SUCCESS;
}