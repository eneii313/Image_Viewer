#include "BaseRunner.h"
#include "ImageManager.h"
#include "FPSCounter.h"

#include "GalleryManager.h"

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

<<<<<<< Updated upstream
	// testing loading icon
	this->loadingIcon = new LoadingIcon(250, 250);

	//load initial textures

	//load initial gallery
	this->gallery = new Gallery(padding, padding*2+36, WINDOW_WIDTH, WINDOW_HEIGHT - (padding*2+36));
=======
	// initialize gallery view
	this->gallery = new GalleryView(padding, padding*2+36, WINDOW_WIDTH, WINDOW_HEIGHT - (padding*2+36));
>>>>>>> Stashed changes

	/*
	namespace fs = std::filesystem;
	std::string path = "Media/Images/";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_regular_file()) {
			gallery->addImage(entry.path().string());
		}
	}*/
	/*
	for (int i = 0; i <  INITIAL_IMAGE_COUNT; ++i) {
		std::stringstream path;
		path << "Media/Images/" << std::setw(2) << std::setfill('0') << i+1 << ".jpg";
		gallery->addImage(path.str());
	}
	*/
	this->gallery->updateImagePositions();
	//TextureDisplay* display = new TextureDisplay();
	//GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);

	this->initCenter = this->window.getView().getCenter();
}

void BaseRunner::run() {
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	
<<<<<<< Updated upstream
=======
	this->gallery->loadImageTextures();
	//this->maxScrollHeight = this->gallery->computeGalleryHeight();
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream

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
			window.setView(view);
=======
			case sf::Event::Closed:
				this->window.close();
				break;
		
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Time currentTime = clock.getElapsedTime();
					if (currentTime - lastClickTime < sf::seconds(0.5)) {
						sf::Vector2i screenCoords(event.mouseButton.x, event.mouseButton.y);
						sf::Vector2f worldCoords = window.mapPixelToCoords(screenCoords, view);
						// Check if mouse position is over any image object
						this->gallery->handleDoubleClick(worldCoords);
						this->viewingImage = true;
					}

					lastClickTime = currentTime;
				}
				break;

			case sf::Event::MouseWheelScrolled:
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
				break;
>>>>>>> Stashed changes
		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {
	GalleryManager::getInstance()->update(elapsedTime);
	GameObjectManager::getInstance()->update(elapsedTime);
	//this->loadingIcon->update(elapsedTime);
}

void BaseRunner::render() {
	this->window.clear(sf::Color(37,37,40));

	this->window.draw(header);
	this->loadingIcon->draw(window);
	this->gallery->draw(window);

	GalleryManager::getInstance()->draw(this->window);
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}