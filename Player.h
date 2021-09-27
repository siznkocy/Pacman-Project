#include "Entity.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <exception>
#include <cstdlib>

class Player : public Entity {
	using Entity::Entity;

private:
	float animationFrame;
	int score = 0;

public:
	Player(Map* mapToLoad, std::string path, sf::Vector2f position);
	
	void updateLogic(sf::Vector2f GhostPos);
	void onDirChange();

	int getScore() const {return score;}
};

Player::Player(Map* mapToLoad, std::string path, sf::Vector2f position) : Entity(mapToLoad, path, position) {
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite.setScale(1.5f,1.5f);
	animationFrame = 0;
}

void Player::updateLogic(sf::Vector2f GhostPos) {

	if (
		sf::Vector2f(sprite.getPosition().x / 16, sprite.getPosition().y/ 16) ==
		sf::Vector2f(GhostPos.x / 16, GhostPos.y / 16)
	) {
		
		std::cout << "PLAYER:you just died :: GAME OVER" << std::endl;
		exit(0);
	}
	
	sprite.setTextureRect(sf::IntRect( floorf(animationFrame / 16.f) * 16, 0, 16, 16));
	//std::cout << sprite.getPosition().x << ": "<<  sprite.getPosition().y << std::endl;
	animationFrame += 4.f;
	animationFrame = fmod(animationFrame, 16.f * 6.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		setDirection(sf::Vector2f(-1, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		setDirection(sf::Vector2f(1, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		setDirection(sf::Vector2f(0, -1));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		setDirection(sf::Vector2f(0, 1));
	}

	mapCollision();
	if (map->getTile(sprite.getPosition()) == 2) {
		map->removeTile(sprite.getPosition());
	 score++;
		std::cout << score << std::endl;
	}
}

void Player::onDirChange() 
{
	sprite.setRotation(atan2(dir.y, dir.x) * (180.f / (float)M_PI));
}