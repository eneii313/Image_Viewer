#pragma once
#include <functional>
#include "IETThread.h"
#include "IWorkerAction.h"

class IExecutionEvent;

class AssetLoader : public IWorkerAction {
private:
	typedef std::string String;

public:
	AssetLoader(String path, IExecutionEvent* event);
	~AssetLoader();

private:
	void onStartTask() override;
	String path;
	IExecutionEvent* event;
	// std::function<void(const sf::Texture&)> callback;

};