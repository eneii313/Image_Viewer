#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Gallery.h"

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1900; // 1920;
	static const int WINDOW_HEIGHT = 1000; // 1080;

	

	static BaseRunner* getInstance();
	static BaseRunner* instance;
	float getFPS();

	BaseRunner();
	void run();

private:

	sf::RenderWindow window;
	sf::Text header;
	Gallery* gallery;

	float padding = 25.0f;
	float fps = 0.0f;

	sf::Vector2f initCenter;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};


