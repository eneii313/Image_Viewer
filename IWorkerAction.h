#pragma once
class IWorkerAction {
public:
	virtual void onStartTask() = 0;
};