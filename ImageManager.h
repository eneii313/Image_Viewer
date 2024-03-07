// stores all the textures being loaded
#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "IExecutionEvent.h"
#include "ThreadPool.h"

class ImageManager {
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;

public:
	static ImageManager* getInstance();
	void loadTextures(IExecutionEvent* event);
	void createTexture(String path);
	sf::Texture* getStreamTextureAt(const int index);

private:
	ImageManager();

	void countAllImages();
	int allImagesCount = 0;

	static ImageManager* sharedInstance;
	TextureList textureList;

	ThreadPool* threadPool;


	const String STREAMING_PATH = "Media/Images/";
	int const NUM_THREADS = 4;
};