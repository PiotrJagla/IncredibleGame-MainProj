#include "headers.h"
#include "Timer.h"

Timer::Timer(float timeMAX) 
{
	m_timeMAX = timeMAX;
}

Timer::~Timer()
{
}

void Timer::update(const float& deltaTime)
{
	m_time += 1000.0f * deltaTime;
}

void Timer::restart(float restartPoint)
{
	m_time = restartPoint;
}

const float Timer::getElapsedTime() const
{
	return m_time;
}

const float Timer::getTimeMAX() const
{
	return m_timeMAX;
}

void Timer::setMAXtime(float timeMAX)
{
	m_timeMAX = timeMAX;
}
