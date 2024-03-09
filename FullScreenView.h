#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "ImageObject.h"
#include "IExecutionEvent.h"

class FullScreenView /* : public IExecutionEvent */ {
public:

	// <int index, std::string texturePath>
	typedef std::unordered_map<int, std::string> HashTable;

	static FullScreenView* getInstance();
	FullScreenView(int windowWidth, int windowHeight);
	// void loadImageTextures();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	//void handleClick(sf::Vector2f mousePosition);

	// void onFinishedExecution(std::string) override;

private:
	static FullScreenView* sharedInstance;

	void updateImagePositions();

	sf::Text returnBtn;
	ImageObject* mainImage;
	std::vector<ImageObject*> images;
	std::string clickedImageName = "";


	const int ICON_COUNT = 8;
	float iconSizeX;
	float iconSizeY;
	const float iconPadding = 20.0f;

};