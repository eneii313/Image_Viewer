#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the update function
 */
#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>
#include "AGameObject.h"
#include <SFML/Graphics.hpp>

typedef std::unordered_map<std::string, AGameObject*> HashTable;
typedef std::vector<AGameObject*> List;

class GameObjectManager
{
public:
	static GameObjectManager* getInstance();
	AGameObject* findObjectByName(AGameObject::String name);
	List getAllObjects();
	int activeObjects();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);
	void addObject(AGameObject* gameObject);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(AGameObject::String name);

private:
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&) {};             // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&) {};  // assignment operator is private
	static GameObjectManager* sharedInstance;

	HashTable gameObjectMap;
	List gameObjectList;

	typedef std::mutex Mutex;
	Mutex guard; // used to avoid race conditions
};

