// displays the textures one at a time
#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"

#include <mutex>

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay : public AGameObject, public IExecutionEvent
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);

	void onFinishedExecution() override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 100.0f; // 0.25f;
	const StreamingType streamingType = SINGLE_STREAM;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;

	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;

	void spawnObject();

	// try mutex guard
	typedef std::mutex Mutex;
	Mutex guard;
};

