#pragma once
#include <chrono>
#include <systems/system.h>

namespace Engine {

	/**
	 * Profiler, logs the duration of it's own existence within a scope
	 */
	class profiler : public System {
	public: 
		profiler(const char* name) : m_Name(name), m_Stopped(false) ///< Constructor which starts the clock
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~profiler() { ///< Destructor which calls the stop function
			if (!m_Stopped)
				stop();
		}

		void start(SystemSignal init = SystemSignal::None, ...) override {}; ///< Necessary implementation of System start pure virtual function

		void stop(SystemSignal close = SystemSignal::None, ...) override { ///< Stops the clock and outputs the time between start and end with relevant details
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();
		
			m_Stopped = true;

			float duration = (end - start) * 0.001f;
			std::cout << m_Name << " Duration: " << duration << "ms" << std::endl;
		}
	private:
		const char* m_Name; ///< A constant char pointer which holds the name passed to the constructor
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint; ///< A Chrono start point to represent the start time
		bool m_Stopped; ///< Boolean which is used to declare the timer as being stopped
	};
}