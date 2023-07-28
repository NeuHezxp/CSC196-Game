#pragma once
#include <chrono>

namespace kiko
{
	class Time
	{
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() :
			m_startTime{ clock::now() },
			m_frameTime{ clock::now() }
		{}

		void Tick();

		void Reset() { m_startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

		float GetTime() const { return m_time; }
		float GetDeltaTime() const { return m_deltaTime * m_timescale; }
		float GetUnscaledDeltaTime() const { return m_deltaTime; }

		float GetTimeScale() const { return m_timescale; }
		float SetTimeScale(float timeScale) { return  m_timescale = timeScale; }

	private:
		float m_time;
		float m_deltaTime;

		float m_timescale = 1;

		clock::time_point m_startTime;
		clock::time_point m_frameTime;
	};
	extern Time g_time;
}