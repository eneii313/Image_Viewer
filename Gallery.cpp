#include <iostream>
#include <filesystem>
#include "Gallery.h"
#include "BaseRunner.h"
#include "StringUtils.h"
#include <thread>

Gallery::Gallery(int posX, int posY, int windowWidth, int windowHeight) {
	this->posX = posX;
	this->posY = posY;
	this->iconSizeX = (windowWidth - iconPadding * (COLUMNS + 1)) / COLUMNS;
	this->iconSizeY = (windowHeight - iconPadding * (ROWS + 1)) / ROWS;


	countAllImages();
	for (int i = 0; i < allImagesCount; ++i) {
		ImageObject* imageObject = new ImageObject(0, 0, this->iconSizeX, this->iconSizeY);
		this->images.push_back(imageObject);
	}
	updateImagePositions();
}

void Gallery::updateImagePositions() {
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

void Gallery::update(sf::Time deltaTime) {
	for (const auto& image : this->images)
		image->update(deltaTime);
}

void Gallery::draw(sf::RenderWindow& window) {
	for (const auto& image : this->images)
		image->draw(window);
}

// count all images in file path + add name into texture list
void Gallery::countAllImages() {
	namespace fs = std::filesystem;

	this->allImagesCount = 0;
	for (const auto& entry : fs::directory_iterator(STREAMING_PATH)) {
		std::string path = entry.path().generic_string();
		this->texturePath.emplace(allImagesCount, path);
		this->allImagesCount++;
	}

	std::cout << "IMAGE COUNT: " << allImagesCount << std::endl;
}

void Gallery::addImageTextures() {
	std::thread loadingThread(&Gallery::loadAllImageTextures, this);
	loadingThread.detach();
}

// Load textures for all images
void Gallery::loadAllImageTextures() {
	for (size_t i = 0; i < this->images.size(); ++i) {
		// std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // try sleep
		std::string texturePath = this->texturePath.at(i);
		
		this->images[i]->setTexture(texturePath);
	}

}


// TODO: fix this if may time
float Gallery::computeGalleryHeight() {
	float totalImageHeight = 0.f;
	for (const auto& image : this->images) {
		totalImageHeight += this->iconSizeY + this->iconPadding;
	}

	// Calculate the maximum allowable position based on the total image height
	return totalImageHeight - BaseRunner::WINDOW_HEIGHT + 100;
}