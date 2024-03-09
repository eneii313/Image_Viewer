#include <iostream>
#include <filesystem>
#include "FullScreenView.h"
#include "ImageManager.h"
#include "BaseRunner.h"
#include "StringUtils.h"


FullScreenView* FullScreenView::sharedInstance = NULL;

FullScreenView* FullScreenView::getInstance() {
	if (sharedInstance == NULL)
		sharedInstance = new FullScreenView(BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT);
	return sharedInstance;
}


FullScreenView::FullScreenView(int windowWidth, int windowHeight) {
	this->iconSizeX = (windowWidth - iconPadding * (ICON_COUNT + 1)) / ICON_COUNT;
	this->iconSizeY = windowHeight * 0.15;
}

void FullScreenView::updateImagePositions() {

	int x = iconPadding;
	int y = BaseRunner::WINDOW_HEIGHT * 0.8;

	for (int i = 0; i < this->ICON_COUNT; ++i) {
		this->images[i]->setPosition(x, y);

		x += iconSizeX + iconPadding;

	}

}

// Load textures for all images
void FullScreenView::loadImageTextures(std::string clickedImageName) {
	this->mainImage = new ImageObject(clickedImageName, 0, 0, BaseRunner::WINDOW_WIDTH - (iconPadding * 2),
																(BaseRunner::WINDOW_HEIGHT * 0.8) - (iconPadding * 2) - 75);
	this->mainImage->setPosition(iconPadding, iconPadding + 75);

	for (int i = 0; i < this->ICON_COUNT; ++i) {
		std::string assetName = ImageManager::getInstance()->getImageNameAt(i);
		ImageObject* imageObject = new ImageObject(assetName, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();

	ImageManager::getInstance()->loadTextures(this);
}

void FullScreenView::update(sf::Time deltaTime) {
	this->mainImage->update(deltaTime);
	for (const auto& image : this->images)
		image->update(deltaTime);

}

void FullScreenView::draw(sf::RenderWindow& window) {
	this->mainImage->draw(window);
	for (const auto& image : this->images)
		image->draw(window);
}

void FullScreenView::onFinishedExecution(std::string assetName) {
	if (!this->mainImage->isTextureLoaded() && assetName == this->mainImage->getAssetName()) {
		this->mainImage->setTexture();
		std::cout << "[FullScreenView] Image loaded: " << assetName << std::endl;
	}
	else {
		for (int i = 0; i < this->images.size(); ++i) {

			if (!this->images[i]->isTextureLoaded() && assetName == this->images[i]->getAssetName()) {
				this->images[i]->setTexture();
				std::cout << "[FullScreenView] Image loaded: " << assetName << std::endl;
				break;
			}
		}
	}
}