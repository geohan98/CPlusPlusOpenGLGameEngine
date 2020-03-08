#pragma once
#include <chrono>
#include "Headers/systems/log.h"

namespace Engine {
	namespace Tools {
		/**
		 * \class Profiler
		 * logs the duration of it's own existence within a scope
		 */
		class profiler {
		private:
			const char* m_Name; ///< A constant char pointer which holds the name passed to the constructor
			std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint; ///< A Chrono start point to represent the start time
		public:
			profiler(const char* name) : m_Name(name) ///< Constructor which starts the clock
			{
				m_StartTimepoint = std::chrono::high_resolution_clock::now();
			}

			~profiler() { ///< Destructor which calls the stop function
				auto endTimepoint = std::chrono::high_resolution_clock::now();

				long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimepoint).time_since_epoch().count();
				long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTimepoint).time_since_epoch().count();

				float duration = (end - start) * 0.001f;
				LOG_CORE_INFO("[PROFILER][{0}][Duration: {1}ms]", m_Name, duration);
			}
		};
	}
}

#define PROFILE_SCOPE(...) Engine::Tools::profiler profile = Engine::Tools::profiler(__VA_ARGS__);