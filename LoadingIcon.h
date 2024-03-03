#include <SFML/Graphics.hpp>
#include <vector>

class LoadingIcon {
public:
	LoadingIcon(int radius, int posX, int posY);
	void initialize();
	void draw(sf::RenderWindow& window);
	void update(sf::Time deltaTime);

private:
	sf::CircleShape circle;
	sf::Texture icon;
	int posX;
	int posY;
	int radius;
	const float rot_speed = 150.0f;
	float angle;
};