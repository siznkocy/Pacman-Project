#pragma once

#include <SFML\Graphics.hpp>

#include "Map.h"

class Entity {

public:
	Entity();
	Entity(Map* mapToLoad, std::string path, sf::Vector2f position);

	void draw(sf::RenderWindow* window);
	void updateLogic() {};

protected:
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f dir, dirBuffer;
	Map* map;

	void setDirection(sf::Vector2f direction);
	void mapCollision();
	bool collidesWithWall(sf::Vector2f pos);

	virtual void onDirChange() {};
	virtual void onWallHit() {};

};

Entity::Entity() {

}

Entity::Entity(Map* mapToLoad, std::string path, sf::Vector2f position) {
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setScale(1.5f, 1.5f);
	sprite.setOrigin(sf::Vector2f(8, 8));
	sprite.setPosition(position);

	map = mapToLoad;
	dir = sf::Vector2f(0, 0);
	dirBuffer = sf::Vector2f(0, 0);
}

inline void Entity::draw(sf::RenderWindow * window) {
	window->draw(sprite);
}

inline void Entity::mapCollision() {
	if (!collidesWithWall(sprite.getPosition() + dirBuffer)) {
		dir = dirBuffer;
		onDirChange();
	}

	if (collidesWithWall(sprite.getPosition() + dir)) {
		dir = sf::Vector2f(0, 0);
		onWallHit();
	}

	sprite.move(sf::Vector2f(dir.x * 2, dir.y * 2));

	sprite.setPosition(sf::Vector2f(
		(float)fmod(sprite.getPosition().x, 448),
		(float)fmod(sprite.getPosition().y, 496)
	));

	if (sprite.getPosition().x < 0) {
		sprite.setPosition(sf::Vector2f(448, sprite.getPosition().y));
	}
}

inline void Entity::setDirection(sf::Vector2f direction) {
	dirBuffer = direction;
}

inline bool Entity::collidesWithWall(sf::Vector2f pos) {
	return
		map->getTile(pos + sf::Vector2f(-8, -8)) == 1 ||
		map->getTile(pos + sf::Vector2f( 7, -8)) == 1 ||
		map->getTile(pos + sf::Vector2f( 7,  7)) == 1 ||
		map->getTile(pos + sf::Vector2f(-8,  7)) == 1;
}