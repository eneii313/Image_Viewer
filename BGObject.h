#pragma once
#include "AGameObject.h"
class BGObject : public AGameObject
{
public:
	BGObject(String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
private:
	const float SPEED_MULTIPLIER = 3000.0f;
};

