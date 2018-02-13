#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

#include <functional>
#include <vector>
#include <SDL2/SDL.h>

class Timer {
private:
	Uint32 mStartTicks;
	Uint32 mPausedTicks;

	bool mPaused;
	bool mStarted;

public:
	typedef std::vector<Timer*> Vec;
	typedef Vec::iterator VecIter;

	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
};


class EventTimer : public Timer {
protected:
	std::function<void()> Callback;
	Uint32		EventFireTime;
	bool		Loop;

public:
	typedef std::vector<EventTimer*> Vec;
	typedef Vec::iterator VecIter;

	EventTimer() {
		this->Callback = nullptr;
		this->SetEventFireTime(0);
		this->SetLoop(false);
	}
	EventTimer(std::function<void()> _callback, Uint32 _eventTime) {
		this->Callback = _callback;
		this->EventFireTime = _eventTime;
		this->SetLoop(false);
	}
	
	void SetEventFireTime(Uint32 _eventTime) { this->EventFireTime = _eventTime; }
	Uint32 GetEventFireTime() { return this->EventFireTime; }
	
	bool IsLooping() { return this->Loop; }
	void SetLoop(bool _loop) { this->Loop = _loop; }
	
	void StartEventTimer() {
		this->start();
	}

	void Update() {
		if (this->getTicks() >= this->GetEventFireTime()) {
			// Stop timer
			this->stop();
			this->Callback();
			
			// If timer loops, restart timer
			if (this->IsLooping()) this->start();
		}
	}
};
#endif
