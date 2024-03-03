#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.0f / FRAME_RATE);
BaseRunner* BaseRunner::instance = NULL;


BaseRunner* BaseRunner::getInstance() {
	if (!instance) {
		instance = new BaseRunner();
	}
	return instance;
}

float BaseRunner::getFPS() {
	return this->fps;
}

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "P2: Photo Viewer", sf::Style::Close) {

	instance = this;
	this->window.setFramerateLimit(int(FRAME_RATE));

	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Roboto.ttf");

	this->header.setString("All Photos");
	this->header.setFont(*font);
	this->header.setCharacterSize(36);
	this->header.setFillColor(sf::Color::White);
	this->header.setPosition(padding, padding);

	// testing loading icon
	this->loadingIcon = new LoadingIcon(50, 300, 300);
	this->loadingIcon->initialize();

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	//TextureDisplay* display = new TextureDisplay();
	//GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	

	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;
	}

}

void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {

		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GameObjectManager::getInstance()->update(elapsedTime);
	this->loadingIcon->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear(sf::Color(37,37,40));
	this->window.draw(header);
	this->loadingIcon->draw(window);

	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}