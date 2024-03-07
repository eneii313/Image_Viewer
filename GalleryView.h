#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
<<<<<<< Updated upstream:Gallery.h
=======
#include <unordered_map>
#include "ImageObject.h"
#include "IExecutionEvent.h"
>>>>>>> Stashed changes:GalleryView.h

class GalleryView : public IExecutionEvent {
public:
<<<<<<< Updated upstream:Gallery.h
	Gallery(int posX, int posY, int windowWidth, int windowHeight);
	void addImage(std::string texturePath);
	void updateImagePositions();
	void draw(sf::RenderWindow& window);

	std::vector<sf::Sprite> images;
=======
	// <int index, std::string texturePath>
	typedef std::unordered_map<int, std::string> HashTable;

	GalleryView(int posX, int posY, int windowWidth, int windowHeight);
	void loadImageTextures();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	void handleDoubleClick(sf::Vector2f mousePosition);
	float computeGalleryHeight();

	void onFinishedExecution() override;

>>>>>>> Stashed changes:GalleryView.h
private:
	const int COLUMNS = 4;
	const int ROWS = 3;
	int posX, posY; //starting pos of entire gallery
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;

};