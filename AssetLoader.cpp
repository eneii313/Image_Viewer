#include "AssetLoader.h"
#include <iostream>
#include "ImageManager.h"
#include "StringUtils.h"
#include "IExecutionEvent.h"

AssetLoader::AssetLoader(String path, IExecutionEvent* event) {
	this->path = path;
	this->event = event;
	// this->callback = callback;
}

AssetLoader::~AssetLoader() {
	// std::cout << "Destroying stream asset loader." << std::endl;
}


void AssetLoader::onStartTask() {
	//simulate loading of very large file
	// IETThread::sleep(1500);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	ImageManager::getInstance()->createTexture(path);

	std::cout << "[AssetLoader] Loaded image texture: " << assetName << std::endl;

	this->event->onFinishedExecution();

	//delete after being done
	delete this;
}

