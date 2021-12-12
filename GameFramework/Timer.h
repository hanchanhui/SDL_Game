#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer() : startTick(0), pauseTick(0), interval(0) {}
	~Timer() {}

	void setInterval(int interval) { this->interval = interval; }
	void start() { startTick = SDL_GetTicks(); } // ���� �ð�
	void pause() { if (pauseTick == 0) { pauseTick = SDL_GetTicks(); } } // ������ �ð�
	void resume() { if (pauseTick != 0) { startTick += SDL_GetTicks() - pauseTick;  pauseTick = 0; } } // �ẹ �ð�
	bool done() { if (pauseTick == 0 && SDL_GetTicks() - startTick >= interval) { start(); return true; }return false; } // �����ϴ� �ð�

	int getstart() { return startTick; }


private:

	int startTick;
	int pauseTick;
	int interval;
};


