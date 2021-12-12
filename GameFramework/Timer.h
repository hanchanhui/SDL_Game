#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer() : startTick(0), pauseTick(0), interval(0) {}
	~Timer() {}

	void setInterval(int interval) { this->interval = interval; }
	void start() { startTick = SDL_GetTicks(); } // start time.
	void pause() { if (pauseTick == 0) { pauseTick = SDL_GetTicks(); } } // Time stopped
	void resume() { if (pauseTick != 0) { startTick += SDL_GetTicks() - pauseTick;  pauseTick = 0; } } // Latent time
	bool done() { if (pauseTick == 0 && SDL_GetTicks() - startTick >= interval) { start(); return true; }return false; } // Time to stop

	int getstart() { return startTick; }


private:

	int startTick;
	int pauseTick;
	int interval;
};


