#include "BaseRunner.h"
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

	this->fpsCounter = new FPSCounter();

	this->initCenter = this->window.getView().getCenter();
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	
	GalleryView::getInstance()->loadImageTextures();
	this->maxScrollHeight = GalleryView::getInstance()->computeGalleryHeight();

	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents(clock);
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;
	}

}

void BaseRunner::processEvents(sf::Clock clock) {
	sf::View view = window.getView();
	sf::Event event;

	if (this->window.pollEvent(event)) {
		switch (event.type) {

		case sf::Event::Closed:
			this->window.close();
			break;
		
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				sf::Time currentTime = clock.getElapsedTime();
				sf::Vector2i screenCoords(event.mouseButton.x, event.mouseButton.y);
				sf::Vector2f worldCoords = window.mapPixelToCoords(screenCoords, view);

				// handles switching to Full Screen
				if (!this->isViewingImage && currentTime - lastClickTime < sf::seconds(0.5)) {
					// Check if mouse position is over any image object
					std::string clickedImage = GalleryView::getInstance()->handleDoubleClick(worldCoords);
					if (clickedImage != "") {
						FullScreenView::getInstance()->loadImageTextures(clickedImage);
						view.setCenter(this->initCenter);
						this->header.setString("< Return");
						this->isViewingImage = true;
					}
				}
				
				else if (this->isViewingImage) {
					// handles clicking another image in Full Screen
					FullScreenView::getInstance()->handleClick(worldCoords);

					// handles switching to Gallery
					sf::FloatRect headerBounds = this->header.getGlobalBounds();
					if (headerBounds.contains(event.mouseButton.x, event.mouseButton.y)) {
						this->header.setString("All Photos");
						this->isViewingImage = false;
					}
				}

				window.setView(view);
				lastClickTime = currentTime;
			}
			break;

		case sf::Event::MouseWheelScrolled:
			if (!this->isViewingImage) {
				view.move(0, -event.mouseWheelScroll.delta * 100);

				// make sure the view doesn't scroll past the top of the object
				if (view.getCenter().y - view.getSize().y / 2.f < 0) {
					view.setCenter(this->initCenter);
				}
				else if (view.getCenter().y >= maxScrollHeight) {
					return;
				}

				window.setView(view);
			}

			break;
		}
	}

	// set position of fps counter
	sf::Vector2f topLeftOfWindow = view.getCenter() - view.getSize() / 2.f;
	sf::Vector2f bottomRightOfWindow = topLeftOfWindow + view.getSize();
	this->fpsCounter->updateFPSPosition(bottomRightOfWindow.y);
	this->fpsCounter->draw(window);
}

void BaseRunner::update(sf::Time elapsedTime) {
	if (this->isViewingImage) {
		FullScreenView::getInstance()->update(elapsedTime);
	}
	else {
		GalleryView::getInstance()->update(elapsedTime);
	}
	
	this->fpsCounter->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear(sf::Color(37,37,40));
	this->window.draw(header);
	if (this->isViewingImage) {
		FullScreenView::getInstance()->draw(window);
	}
	else {
		GalleryView::getInstance()->draw(window);
	}

	this->fpsCounter->draw(window);


	this->window.display();
}