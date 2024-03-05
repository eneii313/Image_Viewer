#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Gallery {
public:
	Gallery(int posX, int posY, int windowWidth, int windowHeight);
	void addImage(std::string texturePath);
	void updateImagePositions();
	void draw(sf::RenderWindow& window);

	std::vector<sf::Sprite> images;
private:
	const int COLUMNS = 4;
	const int ROWS = 3;
	int posX, posY; //starting pos of entire gallery
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;

};