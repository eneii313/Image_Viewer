#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "ImageObject.h"

class Gallery {
public:
	// <int index, std::string texturePath>
	typedef std::unordered_map<int, std::string> HashTable;

	Gallery(int posX, int posY, int windowWidth, int windowHeight);
	void addImageTextures();
	void loadAllImageTextures();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	void handleDoubleClick(sf::Vector2f mousePosition);
	float computeGalleryHeight();

private:
	const int COLUMNS = 4;
	const int ROWS = 3;
	int posX, posY; //starting pos of entire gallery
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;
	int allImagesCount = 0;

	HashTable texturePath;
	std::vector<ImageObject*> images;

	const std::string STREAMING_PATH = "Media/Images/";
	void countAllImages();

	void updateImagePositions();
};