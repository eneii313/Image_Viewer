#pragma once
/// <summary>
/// Listener for calling specific functions after a thread has finished execution.
/// </summary>
class IExecutionEvent {
public:
	virtual void onFinishedExecution() = 0;
};

