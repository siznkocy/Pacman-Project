#include "Entity.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <chrono>

class Ghost : public Entity {
	using Entity::Entity;

public:
	Ghost(Map* mapToLoad, std::string path, sf::Vector2f position);

	void updateLogic();
	sf::Vector2f getPos();

protected:

	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution = std::uniform_int_distribution<int>(0, 3);

	void onDirChange();
	void onWallHit();
	sf::Vector2f randomDirection();
};

Ghost::Ghost(Map* mapToLoad, std::string path, sf::Vector2f position) : Entity(mapToLoad, path, position) {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	setDirection(randomDirection());
}

inline sf::Vector2f Ghost::randomDirection() {
	int rand = distribution(generator);
	sf::Vector2f result;

	switch (rand) {

	case 0:
		result = sf::Vector2f(1, 0);
		break;
	case 1:
		result = sf::Vector2f(-1, 0);
		break;
	case 2:
		result = sf::Vector2f(0, 1);
		break;
	case 3:
		result = sf::Vector2f(0, -1);
		break;
	}

	//std::cout << result.x << " " << result.y << std::endl;

	if (
		collidesWithWall(sprite.getPosition() + result) ||
		dir == result ||
		sf::Vector2f(dir.x * -1, dir.y * -1) == result
	) {
		return randomDirection();
	}

	return result;
}

inline void Ghost::updateLogic() {
	mapCollision();
}

inline sf::Vector2f Ghost::getPos()
{
	return sprite.getPosition();
}

inline void Ghost::onDirChange() {
}

inline void Ghost::onWallHit() {
	setDirection(randomDirection());
}