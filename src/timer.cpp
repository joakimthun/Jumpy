#include "timer.h"

Timer::Timer()
{
	m_start_ticks = 0;
	m_paused_ticks = 0;
	m_started = false;
	m_paused = false;
}

void Timer::start()
{
	m_started = true;
	m_paused = false;

	m_start_ticks = SDL_GetTicks();
	m_paused_ticks = 0;
}

void Timer::stop()
{
	m_started = false;
	m_paused = false;

	m_start_ticks = 0;
	m_paused_ticks = 0;
}

void Timer::pause()
{
	if(m_started && !m_paused)
	{
		m_paused = true;

		m_paused_ticks = SDL_GetTicks() - m_start_ticks;
		m_start_ticks = 0;
	}
}

void Timer::unpause()
{
	if(m_started && m_paused)
	{
		m_paused = false;

		m_start_ticks = SDL_GetTicks() - m_paused_ticks;
		m_paused_ticks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;

	if(m_started)
	{
		if(m_paused)
		{
			time = m_paused_ticks;
		}
		else
		{
			time = SDL_GetTicks() - m_start_ticks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	return m_started;
}

bool Timer::isPaused()
{
	return m_started && m_paused;
}
