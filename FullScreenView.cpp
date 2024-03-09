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
		//std::cout << "[FullScreenView] Updating images pos at row index " << i << std::endl;
		this->images[i]->setPosition(x, y);
		x += iconSizeX + iconPadding;
	}

}

// Load textures for all images
void FullScreenView::loadImageTextures(std::string clickedImageName) {
	// Delete previous instances
	delete this->mainImage;
	for (auto& image : images) {
		delete image;
	}
	images.clear();


	this->mainImage = new ImageObject(clickedImageName, 0, 0, BaseRunner::WINDOW_WIDTH - (iconPadding * 2),
																(BaseRunner::WINDOW_HEIGHT * 0.8) - (iconPadding * 2) - 75);
	this->mainImage->setPosition(iconPadding, iconPadding + 75);


	// set starting index for loading the bottom images
	this->startIndex = ImageManager::getInstance()->getImageNameIndex(clickedImageName);
	int maxIndex = ImageManager::getInstance()->getImageCount() - this->ICON_COUNT;
	if (startIndex > maxIndex)
		startIndex = maxIndex;


	for (int i = this->startIndex; i < (this->startIndex+this->ICON_COUNT); ++i) {
		std::string assetName = ImageManager::getInstance()->getImageNameAt(i);
		//std::cout << "[FullScreenView] Loading images at index " << i << std::endl;
		ImageObject* imageObject = new ImageObject(assetName, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();

	ImageManager::getInstance()->loadTextures(this, this->startIndex, this->startIndex+ICON_COUNT);
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
		this->mainImage->setSizeByTexture();
		//std::cout << "[FullScreenView] Main Image loaded: " << assetName << std::endl;
	}

	for (int i = 0; i < this->images.size(); ++i) {
		if (!this->images[i]->isTextureLoaded() && assetName == this->images[i]->getAssetName()) {
			this->images[i]->setTexture();

			if (this->images[i]->getAssetName() == this->mainImage->getAssetName())
				this->images[i]->setBorder();
			break;
		}
	}


}

void FullScreenView::handleClick(sf::Vector2f mousePosition) {
	for (auto& imageObject : this->images) {
		if (imageObject->isMouseOver(mousePosition)) {
			// Handle click event for the image object
			//std::cout << "Click on image object detected! Image " << imageObject->getAssetName() << std::endl;
			this->mainImage->setAssetName(imageObject->getAssetName());
			this->mainImage->setTexture();
			this->mainImage->setSizeByTexture();

			for (auto& imageObject2 : this->images)
				imageObject2->removeBorder();

			imageObject->setBorder();

			break;
		}
	}
}