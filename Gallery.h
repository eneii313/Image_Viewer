#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ImageObject.h"

class Gallery {
public:
	Gallery(int posX, int posY, int windowWidth, int windowHeight);
	void addImage(std::string texturePath);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
private:
	const int COLUMNS = 4;
	const int ROWS = 3;
	int posX, posY; //starting pos of entire gallery
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;
	int allImagesCount = 0;

	std::vector<ImageObject*> images;

	void updateImagePositions();

	const std::string STREAMING_PATH = "Media/Images/";
	void countAllImages();
};