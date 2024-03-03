#include "AssetLoader.h"
#include <iostream>
#include "TextureManager.h"
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
	// std::cout << "Running stream asset loader " << std::endl;
	//simulate loading of very large file
	IETThread::sleep(1500);

	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);

	std::cout << "[AssetLoader] Loaded streaming texture: " << assetName << std::endl;

	this->event->onFinishedExecution();

	//delete after being done
	delete this;
}

