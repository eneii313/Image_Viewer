#pragma once
#include "ThreadPool.h"
#include "PoolWorkerThread.h"

ThreadPool::ThreadPool(String name, int numThreads) {
	this->name = name;
	this->numThreads = numThreads;

	for (int i = 0; i < numThreads; i++) {
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}

}

ThreadPool::~ThreadPool()
{
	// std::cout << "Destroying thread pool." << std::endl;
	this->stopScheduler();

	this->activeThreads.clear();
	while (this->inactiveThreads.empty() == false) {
		this->inactiveThreads.pop();

	}
}

void ThreadPool::startScheduler() {
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler() {
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action) {
	this->pendingActions.push(action);
}

void ThreadPool::run() {
	while (this->running) {
		// check if there are any pending actions
		if (this->pendingActions.empty() == false) {
			if (this->inactiveThreads.empty() == false) {
				// schedule the task
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				// start the task in front of the queue
				workerThread->assignTask(this->pendingActions.front());
				workerThread->start();
				this->pendingActions.pop();
			}
			else {
				// std::cout << "[ThreadPool " << this->name << "] No more available worker threads." << std::endl;
			}
		}
		else {
			// std::cout << "[ThreadPool " << this->name << "] No actions scheduled." << std::endl;
		}
	}
}

void ThreadPool::onFinished(int threadID) {
	if (this->activeThreads[threadID] != nullptr) {
		// create a fresh instance of a thread worker after execution
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}