#include "AssetLoader.h"
#include <iostream>
#include "ImageManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

AssetLoader::AssetLoader(String path, IExecutionEvent* event) {
	this->path = path;
	this->event = event;
}

AssetLoader::~AssetLoader() {
	// std::cout << "Destroying stream asset loader." << std::endl;
}


void AssetLoader::onStartTask() {
	//simulate loading of very large file
	IETThread::sleep(500);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = tokens.back();

	if (ImageManager::getInstance()->isImageLoaded(assetName))
		std::cerr << "[AssetLoader] " << assetName + " is already loaded." << std::endl;
	else {
		ImageManager::getInstance()->createTexture(path, assetName);
		//std::cout << "[AssetLoader] Loaded image texture: " << assetName << std::endl;
	}

	this->event->onFinishedExecution(assetName);

	//delete after being done
	delete this;
}
