#pragma once
#include "SFML/Graphics.hpp"
#include "LoadingIcon.h"

class ImageObject {
public:
	ImageObject(std::string assetName, int posX, int posY, int iconSizeX, int iconSizeY);
	void setAssetName(std::string assetName);
	void setTexture();
	void setPosition(int posX, int posY);
	void setSizeByTexture();
	void setBorder();
	void removeBorder();

	bool isMouseOver(const sf::Vector2f& mousePosition);
	void handleDoubleClick();

	std::string getAssetName() const;
	bool isTextureLoaded() const;
	float getImageEndPos();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);

	sf::Sprite sprite;

private:
	std::string assetName;
	int iconSizeX;
	int iconSizeY;

	sf::RectangleShape border;
	bool textureLoaded;
	bool showBorder = false;

	LoadingIcon* loadingIcon;
};