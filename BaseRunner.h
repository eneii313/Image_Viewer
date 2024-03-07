#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
<<<<<<< Updated upstream
#include "LoadingIcon.h"
#include "Gallery.h"
=======
#include "GalleryView.h"
#include "FPSCounter.h"
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
	LoadingIcon* loadingIcon;
	Gallery* gallery;
=======
	GalleryView* gallery;
	FPSCounter* fpsCounter;
>>>>>>> Stashed changes

	float padding = 25.0f;
	float fps = 0.0f;
	const int INITIAL_IMAGE_COUNT = 12; //4*3

	sf::Vector2f initCenter;
	bool viewingImage = false;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};


