// stores all the textures being loaded
#pragma once
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "IExecutionEvent.h"
#include "ThreadPool.h"

class TextureManager
{
public:
	typedef std::string String;
	typedef std::vector<sf::Texture*> TextureList;
	typedef std::unordered_map<String, TextureList> HashTable;

public:
	static TextureManager* getInstance();
	void loadFromAssetList(); //loading of all assets needed for startup
	void loadSingleStreamAsset(int index, IExecutionEvent* event); //loads a single streaming asset based on index in directory
	void loadStreamingAssets();
	sf::Texture* getFromTextureMap(const String assetName, int frameIndex);
	int getNumFrames(const String assetName);

	sf::Texture* getImageTextureFromList(const int index);
	int getNumLoadedStreamTextures() const;
	int allAssetsLoaded() const;

	void instantiateAsTexture(String path, String assetName, bool isStreaming);


private:
	TextureManager();
	TextureManager(TextureManager const&) {};             // copy constructor is private
	TextureManager& operator=(TextureManager const&) {};  // assignment operator is private
	static TextureManager* sharedInstance;

	HashTable textureMap;
	TextureList baseTextureList;
	TextureList streamTextureList;
	ThreadPool* threadPool;

	const std::string STREAMING_PATH = "Media/Images/"; // "Media/Streaming/";
	int streamingAssetCount = 0;

	void countStreamingAssets();

	int const NUM_THREADS = 4;
};