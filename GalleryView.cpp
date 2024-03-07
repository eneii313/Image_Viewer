#include <iostream>
<<<<<<< Updated upstream:Gallery.cpp
#include "Gallery.h"
#include "BaseRunner.h"

Gallery::Gallery(int posX, int posY, int windowWidth, int windowHeight) { 
=======
#include <filesystem>
#include "GalleryView.h"
#include "ImageManager.h"
#include "BaseRunner.h"
#include "StringUtils.h"

GalleryView::GalleryView(int posX, int posY, int windowWidth, int windowHeight) {
>>>>>>> Stashed changes:GalleryView.cpp
	this->posX = posX;
	this->posY = posY;
	this->iconSizeX = (windowWidth - iconPadding * (COLUMNS + 1)) / COLUMNS;
	this->iconSizeY = (windowHeight - iconPadding * (ROWS + 1)) / ROWS;
}

void Gallery::addImage(std::string texturePath) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath))
		std::cerr << texturePath + " not found." << std::endl;

<<<<<<< Updated upstream:Gallery.cpp
	sf::Sprite sprite(*texture);

	float scaleX = this->iconSizeX / texture->getSize().x;
	float scaleY = this->iconSizeY / texture->getSize().y;

	// resize image texture
	sprite.setScale(scaleX, scaleY);
	
	this->images.push_back(sprite);
=======
	countAllImages();
	for (int i = 0; i < allImagesCount; ++i) {
		ImageObject* imageObject = new ImageObject(i, 0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();
>>>>>>> Stashed changes:GalleryView.cpp
}


// TODO: make this spawnObject
void GalleryView::updateImagePositions() {
	int x = this->posX;
	int y = this->posY;

	for (int i = 0; i < this->images.size(); ++i) {
		this->images[i].setPosition(x, y);

		x += iconSizeX + iconPadding;

		if ((i + 1) % COLUMNS == 0) {
			x = posX;
			y += iconSizeY + iconPadding;
		}
	}
<<<<<<< Updated upstream:Gallery.cpp
=======

}

void GalleryView::update(sf::Time deltaTime) {
	for (const auto& image : this->images)
		image->update(deltaTime);
>>>>>>> Stashed changes:GalleryView.cpp
}

void GalleryView::draw(sf::RenderWindow& window) {
	for (const auto& image : this->images)
<<<<<<< Updated upstream:Gallery.cpp
		window.draw(image);
=======
		image->draw(window);
}

// count all images in file path + add name into texture list
void GalleryView::countAllImages() {
	namespace fs = std::filesystem;

	this->allImagesCount = 0;
	for (const auto& entry : fs::directory_iterator(STREAMING_PATH)) {
		std::string path = entry.path().generic_string();
		this->texturePath.emplace(allImagesCount, path);
		this->allImagesCount++;
	}

	std::cout << "IMAGE COUNT: " << allImagesCount << std::endl;
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
			std::cout << "Double-click on image object detected! Image " << this->texturePath.at(i) << std::endl;
			break;
		}
		i++;
	}
}

// replace all loa
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
>>>>>>> Stashed changes:GalleryView.cpp
}