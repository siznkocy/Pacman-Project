#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Map {
	public:
		Map(std::string filePath);
		~Map();

		void draw(sf::RenderWindow* window);
		int getTile(sf::Vector2f pos);
		void removeTile(sf::Vector2f pos);

	private:
		int ASCI_Arr[28][31] = { 0 };
		sf::Texture texture;
		sf::RectangleShape wall = sf::RectangleShape(sf::Vector2f(16,16));
};

Map::Map(std::string filePath) {

	std::ifstream PcFile(filePath);

	sf::Vector2i coord = sf::Vector2i(0, 0);
	while ( !PcFile.eof() ) {
		char block;
		PcFile >> block;
		ASCI_Arr[coord.x][coord.y] = block - '0';
		if ( PcFile.peek() == '\n') {
			coord.x++;
			coord.y = 0;
		}
		else {
			coord.y++;
		}
	}

	texture = sf::Texture();
	texture.loadFromFile("Files/tileMap.png");
	wall.setTexture( &texture );
}

Map::~Map() {

}

void Map::draw(sf::RenderWindow* window) {

	for (int x = 0; x < 25; x++) {
		for (int y = 0; y < 31; y++) {

			if ( ASCI_Arr[x][y] != 0 ) {
				wall.setPosition((float)x * 16, (float)y * 16);
				wall.setTextureRect(sf::IntRect((ASCI_Arr[x][y] - 1) * 16, 0, 16, 16));
				window->draw(wall);
			}
		}
	}

}

int Map::getTile(sf::Vector2f pos) {
	return ASCI_Arr[(int)pos.x / 16][(int)pos.y / 16];
}

void Map::removeTile(sf::Vector2f pos) {
	ASCI_Arr[(int)pos.x / 16][(int)pos.y / 16] = 0;
}