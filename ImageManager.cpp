#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "ImageManager.h"
#include "StringUtils.h"
#include "AssetLoader.h"

ImageManager* ImageManager::sharedInstance = NULL;

ImageManager* ImageManager::getInstance() {
	if (sharedInstance == NULL)
		sharedInstance = new ImageManager();
	return sharedInstance;
}

ImageManager::ImageManager() {
	this->countAllImages();

	this->threadPool = new ThreadPool("Image Loader TP", this->NUM_THREADS);
	this->threadPool->startScheduler();
}


void ImageManager::loadTextures(IExecutionEvent* event) {\
	for (const auto& file : std::filesystem::directory_iterator(STREAMING_PATH)) {
		String path = file.path().generic_string();

		AssetLoader* assetLoader = new AssetLoader(path, event);
		this->threadPool->scheduleTask(assetLoader);
	}
}

void ImageManager::countAllImages() {
	this->allImagesCount = 0;
	for (const auto& file : std::filesystem::directory_iterator(STREAMING_PATH)) {
		String path = file.path().generic_string();
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName = tokens.back();
		this->textureList.push_back(assetName);

		this->allImagesCount++;
	}

	std::cout << "[ImageManager] IMAGE COUNT: " << allImagesCount << std::endl;
}

void ImageManager::createTexture(String texturePath, String fileName) {
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(texturePath)) {
		std::cerr << texturePath + " not found." << std::endl;
		delete texture;
		return;
	}
	mutex.lock();
	this->textureMap[fileName] = texture;
	mutex.unlock();
}

sf::Texture* ImageManager::getImageTexture(const String fileName) {
	// return this->textureMap[fileName];
	auto it = this->textureMap.find(fileName);
	if (it != this->textureMap.end()) {
		// Check if the retrieved pointer is not null
		if (it->second != nullptr) {
			return it->second;
		}
		else {
			// Handle case where texture is not loaded successfully
			std::cerr << "[ImageManager] Texture for file " << fileName << " is null." << std::endl;
			return nullptr;
		}
	}
	else {
		// Handle case where file name is not found in textureMap
		std::cerr << "[ImageManager] Texture for file " << fileName << " not found." << std::endl;
		return nullptr;
	}
}

int ImageManager::getImageCount() {
	return this->allImagesCount;
}

std::string ImageManager::getImageNameAt(const int index) {
	if (index >= 0 && index < this->textureList.size())
		return this->textureList[index];
	else return nullptr;
}