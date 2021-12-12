#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer() : startTick(0), pauseTick(0), interval(0) {}
	~Timer() {}

	void setInterval(int interval) { this->interval = interval; }
	void start() { startTick = SDL_GetTicks(); } // 시작 시간
	void pause() { if (pauseTick == 0) { pauseTick = SDL_GetTicks(); } } // 정지된 시간
	void resume() { if (pauseTick != 0) { startTick += SDL_GetTicks() - pauseTick;  pauseTick = 0; } } // 잠복 시간
	bool done() { if (pauseTick == 0 && SDL_GetTicks() - startTick >= interval) { start(); return true; }return false; } // 정지하는 시간

	int getstart() { return startTick; }


private:

	int startTick;
	int pauseTick;
	int interval;
};


