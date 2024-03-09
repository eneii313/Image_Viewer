#include <SFML/Graphics.hpp>

class LoadingIcon {
public:
	LoadingIcon(int posX, int posY, int spriteHeight, float scale);
	void setPosition(int posX, int posY);
	void draw(sf::RenderWindow& window);
	void update(sf::Time deltaTime);

private:
	sf::Sprite sprite;
	sf::Texture icon;
	const float rot_speed = 150.0f;
};