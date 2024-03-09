#pragma once
#include <string>
/// <summary>
/// Listener for calling specific functions after a thread has finished execution.
/// </summary>
class IExecutionEvent {
public:
	virtual void onFinishedExecution(std::string assetName) = 0;
};

