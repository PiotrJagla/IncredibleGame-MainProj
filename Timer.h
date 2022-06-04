#pragma once
class Timer
{
public:
	float m_timeMAX;
	float m_time;

	float m_speed;

public:
	Timer(float timeMAX = 0, float speed = 0);
	~Timer();

	void update(const float& deltaTime);

	void restart(float restartPoint = 0);

	const float getElapsedTime() const;
	const float getTimeMAX() const;
	

	void setMAXtime(float maxTIME);
	void setSpeed(float speed);


};

