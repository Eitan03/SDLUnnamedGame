#include "Timer.h"

Timer::Timer() :
	startingTime(0), ticks(0), paused(false), started(false), pauseTime(0)
{

}

Timer::~Timer()
{
}

bool Timer::Started()
{
	return started;
}

bool Timer::Paused()
{
	return paused;
}

void Timer::Start()
{
	startingTime = SDL_GetTicks();
	started = true;
	paused = false;
}

void Timer::Pause()
{
	if (!started) return;
	pauseTime = SDL_GetTicks();
	paused = true;
}

void Timer::Continue()
{
	if (!started) return;
	if (paused) {
		startingTime = SDL_GetTicks() - pauseTime;
		paused = false;
	}
}

void Timer::stop()
{
	started = false;
	paused = false;
}

int Timer::GetTime()
{
	if (!started) return 0;
	if (paused) return pauseTime - startingTime;
	return SDL_GetTicks() - startingTime;
}
