#include <iostream>
#include <filesystem>
#include "GalleryView.h"
#include "ImageManager.h"
#include "BaseRunner.h"
#include "StringUtils.h"

GalleryView* GalleryView::sharedInstance = NULL;

GalleryView* GalleryView::getInstance() {
	if (sharedInstance == NULL)
		sharedInstance = new GalleryView(25, 86, BaseRunner::WINDOW_WIDTH, BaseRunner::WINDOW_HEIGHT);
	return sharedInstance;
}

GalleryView::GalleryView(int posX, int posY, int windowWidth, int windowHeight) {
	this->posX = posX;
	this->posY = posY;
	this->iconSizeX = (windowWidth - iconPadding * (COLUMNS + 1)) / COLUMNS;
	this->iconSizeY = (windowHeight - iconPadding * (ROWS + 1)) / ROWS;

	int imageCount = ImageManager::getInstance()->getImageCount();
	for (int i = 0; i < imageCount; ++i) {
		std::string assetName = ImageManager::getInstance()->getImageNameAt(i);
		ImageObject* imageObject = new ImageObject(assetName, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();
}


void GalleryView::updateImagePositions() {

	int x = this->posX;
	int y = this->posY;

	for (int i = 0; i < this->images.size(); ++i) {
		this->images[i]->setPosition(x, y);

		x += iconSizeX + iconPadding;

		if ((i + 1) % COLUMNS == 0) {
			x = posX;
			y += iconSizeY + iconPadding;
		}
	}

}

void GalleryView::update(sf::Time deltaTime) {
	for (const auto& image : this->images)
		image->update(deltaTime);

}


void GalleryView::draw(sf::RenderWindow& window) {
	for (const auto& image : this->images)
		image->draw(window);
}



// Load textures for all images
void GalleryView::loadImageTextures() {
	ImageManager::getInstance()->loadTextures(this);
}


// TODO: fix this if may time
float GalleryView::computeGalleryHeight() {
	float totalImageHeight = 0.f;
	for (const auto& image : this->images) {
		totalImageHeight += this->iconSizeY + this->iconPadding;
	}

	// Calculate the maximum allowable position based on the total image height
	return totalImageHeight - BaseRunner::WINDOW_HEIGHT + 100;
}


void GalleryView::handleDoubleClick(sf::Vector2f mousePosition) {
	for (auto& imageObject : this->images) {
		if (imageObject->isMouseOver(mousePosition)) {
			// Handle double-click event for the image object
			std::cout << "Double-click on image object detected! Image " << imageObject->getAssetName() << std::endl;
			FullScreenView::getInstance()->loadImageTextures(imageObject->getAssetName());
			break;
		}
	}
}

void GalleryView::onFinishedExecution(std::string assetName) {
	for (int i = 0; i < this->images.size(); ++i) {
		
		if (!this->images[i]->isTextureLoaded() && assetName == this->images[i]->getAssetName()) {
			this->images[i]->setTexture();
			//std::cout << "[GalleryView] Image loaded: " << assetName << std::endl;
			break;
		}
		
		/*
		if (!this->images[i]->isTextureLoaded()) {
			this->images[i]->setTexture();
			std::cout << "[GalleryView] Image loaded: " << i << std::endl;
		}
		*/
	}
}