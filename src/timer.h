#pragma once

#include <SDL/SDL.h>

class Timer {
private:
	Uint32 m_start_ticks;
	Uint32 m_paused_ticks;
	bool m_started;
	bool m_paused;

public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();
};
