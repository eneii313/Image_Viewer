#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "ImageObject.h"
#include "IExecutionEvent.h"

class GalleryView : public IExecutionEvent {
public:

	// <int index, std::string texturePath>
	typedef std::unordered_map<int, std::string> HashTable;

	static GalleryView* getInstance();
	GalleryView(int posX, int posY, int windowWidth, int windowHeight);
	void loadImageTextures();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	std::string handleDoubleClick(sf::Vector2f mousePosition);
	float computeGalleryHeight();

	void onFinishedExecution(std::string) override;

private:
	static GalleryView* sharedInstance;

	void updateImagePositions();

	std::vector<ImageObject*> images;

	const int COLUMNS = 4;
	const int ROWS = 3;
	int posX, posY; //starting pos of entire gallery
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;

};