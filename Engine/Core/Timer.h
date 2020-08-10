#pragma once
#include <chrono>

namespace nc
{
	class Timer
	{
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = std::chrono::duration<clock::rep, clock::period>;

	public:
		Timer() : m_timePoint(clock::now()) {}

		void Reset();
		clock::rep ElapsedTicks();
		clock::rep TicksPerSecond();

		double ElapsedSeconds();

	protected:
		clock::time_point m_timePoint;
	};

	class FrameTimer : public Timer
	{
	public:
		void Tick();

		float DeltaTime() { return m_dt; }
		float FPS() { return m_fps; }

	protected:
		float m_dt{ 0 };
		float m_fps{ 0 };
		float m_frameTime{ 0 };
		int m_frameCount{ 0 };
	};
}
