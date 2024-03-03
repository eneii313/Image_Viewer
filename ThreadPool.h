#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"

class PoolWorkerThread;
class IWorkerAction;
class IFinishedTask {
public:
	// for every job finished, call this
	virtual void onFinished(int threadID) = 0;
};

// CLass that can hold N threads that can be reused. This is a thread itself, because it needs to constantly schedule tasks.
class ThreadPool : public IETThread, public IFinishedTask {
private:
	typedef std::string String;
	typedef std::queue<PoolWorkerThread*> ThreadList;
	typedef std::unordered_map<int, PoolWorkerThread*> ActiveThreadMap;
	typedef std::queue<IWorkerAction*> ActionList;

public:
	ThreadPool(String name, int numThreads);
	~ThreadPool();

	void startScheduler();
	void stopScheduler();
	void scheduleTask(IWorkerAction* action);

private:
	void run() override;
	void onFinished(int threadID) override;

	String name;
	bool running = false;
	int numThreads = 0;
	ActiveThreadMap activeThreads;
	ThreadList inactiveThreads;
	ActionList pendingActions;
};