#include <iostream>
#include <filesystem>
#include "GalleryView.h"
#include "ImageManager.h"
#include "BaseRunner.h"
#include "StringUtils.h"

GalleryView::GalleryView(int posX, int posY, int windowWidth, int windowHeight) {
	this->posX = posX;
	this->posY = posY;
	this->iconSizeX = (windowWidth - iconPadding * (COLUMNS + 1)) / COLUMNS;
	this->iconSizeY = (windowHeight - iconPadding * (ROWS + 1)) / ROWS;

	int imageCount = ImageManager::getInstance()->getImageCount();
	for (int i = 0; i < imageCount; ++i) {
		ImageObject* imageObject = new ImageObject(i, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();
}


// TODO: make this spawnObject
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



/*
void GalleryView::addImageTextures() {
	std::thread loadingThread(&GalleryView::loadAllImageTextures, this);
	loadingThread.detach();
}
*/

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
	int i = 0;
	for (auto& imageObject : this->images) {
		if (imageObject->isMouseOver(mousePosition)) {
			// Handle double-click event for the image object
			// std::cout << "Double-click on image object detected! Image " << this->texturePath.at(i) << std::endl;
			break;
		}
		i++;
	}
}

void GalleryView::onFinishedExecution() {
	/*
		for (size_t i = 0; i < this->images.size(); ++i) {

		// std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // try sleep

		std::string texturePath = this->texturePath.at(i);



		this->images[i]->setTexture(texturePath);



		// std::cout << "Image " << i <<" Texture path" << texturePath << std::endl;

	}
	*/
	//this->loadImage();
}