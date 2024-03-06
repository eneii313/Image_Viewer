#include "BaseRunner.h"
#include  "GameObjectManager.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

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

	// initialize gallery view
	this->gallery = new Gallery(padding, padding*2+36, WINDOW_WIDTH, WINDOW_HEIGHT - (padding*2+36));

	this->fpsCounter = new FPSCounter();

	this->initCenter = this->window.getView().getCenter();
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	
	this->gallery->addImageTextures();
	this->maxScrollHeight = this->gallery->computeGalleryHeight();

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

	
		case sf::Event::MouseWheelScrolled:
			sf::View view = window.getView();
			view.move(0, -event.mouseWheelScroll.delta * 100);
			
			// make sure the view doesn't scroll past the top of the object
			if (view.getCenter().y - view.getSize().y / 2.f < 0) {
				view.setCenter(this->initCenter);
			}

			sf::Vector2f topLeftOfWindow = view.getCenter() - view.getSize() / 2.f;
			sf::Vector2f bottomRightOfWindow = topLeftOfWindow + view.getSize();
			this->fpsCounter->updateFPSPosition(bottomRightOfWindow.y);

			window.setView(view);

			this->fpsCounter->draw(window);
		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	this->gallery->update(elapsedTime);
	this->fpsCounter->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear(sf::Color(37,37,40));

	this->window.draw(header);
	this->gallery->draw(window);
	this->fpsCounter->draw(window);


	this->window.display();
}