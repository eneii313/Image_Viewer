#pragma once
#include <iostream>
#include "StringUtils.h"
#include "GalleryManager.h"
#include "BaseRunner.h"

GalleryManager* GalleryManager::sharedInstance = NULL;

GalleryManager::GalleryManager() {
}

GalleryManager* GalleryManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new GalleryManager();
	}	
	return sharedInstance;  

}

void GalleryManager::setGallery(Gallery* gallery) {
	this->gallery = gallery;
}

void GalleryManager::update(sf::Time deltaTime) {
	if (!allImagesLoaded()) {
		this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

		if (this->ticks > this->STREAMING_LOAD_DELAY) {
			this->ticks = 0;
			this->spawnImage();
		}
		this->gallery->updateImagePositions();
	}
}

void GalleryManager::countAllImages() {
	this->allImagesCount = 0;

	namespace fs = std::filesystem;
	for (const auto& entry : fs::directory_iterator(STREAMING_PATH)) {
		this->allImagesCount++;
	}
}

bool GalleryManager::allImagesLoaded() {
	return this->gallery->images.size() >= this->allImagesCount - 1;
}

void GalleryManager::spawnImage() {
	int index = this->gallery->images.size();
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH)) {
		if (index == fileNum)
		{
			
			// initial code
			//simulate loading of very large file
			//IETThread::sleep(200);

			//<code here for loading asset>
			std::string path = entry.path().generic_string();

			// Check if the texture is already loaded
			if (this->textureMap.find(path) == this->textureMap.end()) {
				// Texture not loaded, load it
				this->gallery->addImage(path);
				std::vector<String> tokens = StringUtils::split(path, '/');
				String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
				this->instantiateAsTexture(path, assetName);
				std::cout << "[GalleryManager] Loaded single streaming texture: " << path << std::endl;

				break;
			}
			
			// for stream asset loader
			//String path = entry.path().generic_string();
			//AssetLoader* assetLoader = new AssetLoader(path, event);
			//this->threadPool->scheduleTask(assetLoader);
			break;
		}

		fileNum++;
	}
}

void GalleryManager::instantiateAsTexture(String path, String assetName){
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile(path);
	this->textureMap[assetName].push_back(texture);

	this->textureList.push_back(texture);
}

//draws the object if it contains a sprite
void GalleryManager::draw(sf::RenderWindow& window) {
	gallery->draw(window);
}