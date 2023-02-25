#pragma once
#include <chrono>

using namespace std::chrono;

class Timer
{
public:
	Timer();
	~Timer();

	static Timer& Get();

	void Tick();
	void Reset();

	double getElapsedMs();
	double getElapsedS() const;

	double TotalTimeS() const;
	double TotalTimeMs() const;

private:
	high_resolution_clock::time_point m_t0, m_t1;

	double m_elapsedTime;
	double m_totalTime;
};

