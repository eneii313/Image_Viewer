#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
class BaseRunner : private sf::NonCopyable
{
public:
	static const sf::Time	TIME_PER_FRAME;
	static const int WINDOW_WIDTH = 1920; // 1920;
	static const int WINDOW_HEIGHT = 800; // 1080;

	static BaseRunner* getInstance();
	static BaseRunner* instance;
	float getFPS();

	BaseRunner();
	void run();

private:

	sf::RenderWindow		window;
	float fps = 0.0f;

	void render();
	void processEvents();
	void update(sf::Time elapsedTime);
};


