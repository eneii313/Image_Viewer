#include <iostream>
#include <filesystem>
#include "ImageManager.h"
#include "StringUtils.h"
#include "AssetLoader.h"

ImageManager* ImageManager::sharedInstance = NULL;

ImageManager* ImageManager::getInstance() {
	if (sharedInstance == NULL) {
		//initialize
		sharedInstance = new ImageManager();
	}

	return sharedInstance;
}

ImageManager::ImageManager() {
	this->countAllImages();

	this->threadPool = new ThreadPool("Image Loader TP", this->NUM_THREADS);
	// this->threadPool->startScheduler();
}


void ImageManager::loadTextures(IExecutionEvent* event) {
	for (const auto& file : std::filesystem::directory_iterator(STREAMING_PATH)) {
		String path = file.path().generic_string();
		AssetLoader* assetLoader = new AssetLoader(path, event);
	}
}

void ImageManager::countAllImages() {
	this->allImagesCount = 0;
	for (const auto& file : std::filesystem::directory_iterator(STREAMING_PATH)) {
		this->allImagesCount++;
	}

	std::cout << "IMAGE COUNT: " << allImagesCount << std::endl;
}

void ImageManager::createTexture(String texturePath) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath)) {
		std::cerr << texturePath + " not found." << std::endl;
		return;
	}
	this->textureList.push_back(texture);
}

sf::Texture* ImageManager::getStreamTextureAt(const int index) {
	return this->textureList[index];

}