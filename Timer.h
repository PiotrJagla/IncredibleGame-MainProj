#pragma once
class Timer
{
public:
	float m_timeMAX;
	float m_time;
public:
	Timer(float timeMAX = 0);
	~Timer();

	void update(const float& deltaTime);

	void restart(float restartPoint = 0);

	const float getElapsedTime() const;
	const float getTimeMAX() const;
	

	void setMAXtime(float maxTIME);


};

