#include "PoolWorkerThread.h"

#include "IWorkerAction.h"
#include "ThreadPool.h"

PoolWorkerThread::PoolWorkerThread(int id, IFinishedTask* finishedTask) {
	this->id = id;
	this->finishedTask = finishedTask;
}

PoolWorkerThread::~PoolWorkerThread() {
	// std::cout << "Destroying pool worker thread." << std::endl;
}

int PoolWorkerThread::getThreadID() {
	return this->id;
}

void PoolWorkerThread::assignTask(IWorkerAction* action) {
	this->action = action;
}

void PoolWorkerThread::run() {
	this->action->onStartTask();
	this->finishedTask->onFinished(id);
}