#pragma once
#include <unordered_map>
#include <filesystem>
#include "SFML/Graphics.hpp"
#include "IconObject.h"
#include "Gallery.h"

// CLASS THAT HANDLES LOADING IMAGES
class GalleryManager {
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;

public:
	GalleryManager();
	static GalleryManager* getInstance();
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow& window);
	void setGallery(Gallery* gallery);
private:
	static GalleryManager* sharedInstance;

	Gallery* gallery;

	const String STREAMING_PATH = "Media/Images/";

	HashTable textureMap;
	TextureList textureList;

	const float STREAMING_LOAD_DELAY = 100.0f;
	float ticks = 0.0f;

	int allImagesCount = 0;
	void countAllImages();
	bool allImagesLoaded();

	void instantiateAsTexture(String path, String assetName);
	void spawnImage();
};