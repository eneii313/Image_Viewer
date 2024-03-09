// stores all the textures being loaded
#pragma once
#include <unordered_map>
#include <mutex>
#include "SFML/Graphics.hpp"
#include "IExecutionEvent.h"
#include "ThreadPool.h"

class ImageManager {
public:
	typedef std::string String;
	typedef std::vector<String> List;
	typedef std::unordered_map<String, sf::Texture*> HashTable;

public:
	static ImageManager* getInstance();
	void loadTextures(IExecutionEvent* event);
	void createTexture(String path, String fileName);
	sf::Texture* getImageTexture(const String fileName);
	String getImageNameAt(const int index);
	int getImageCount();
	bool isImageLoaded(String fileName);

private:
	ImageManager();

	void countAllImages();
	int allImagesCount = 0;

	static ImageManager* sharedInstance;
	List textureList;
	HashTable textureMap;

	ThreadPool* threadPool;
	std::mutex mutex;


	const String STREAMING_PATH = "Media/Images/";
	int const NUM_THREADS = 4;
};