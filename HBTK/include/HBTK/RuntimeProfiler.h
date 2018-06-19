#pragma once
/*////////////////////////////////////////////////////////////////////////////
RuntimeProfiler.h

Class to do basic profiling of applications at runtime.

Copyright 2017-2018 HJA Bird

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/////////////////////////////////////////////////////////////////////////////

#include <atomic>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace HBTK {
	class RuntimeProfiler {
	public:
		RuntimeProfiler(const char* function, const int line_no);
		RuntimeProfiler(const char* function, const int line_no, bool timing);
		~RuntimeProfiler();
	private:
		std::string m_string;
		bool m_timing;
		std::chrono::time_point<std::chrono::steady_clock> t_start;
	};

	class GlobalRuntimeProfiler {
	public:
		static GlobalRuntimeProfiler& get_instance();
		static void set_file(std::string file_name);
		static void new_timeset_now();
	private:
		friend class RuntimeProfiler;
		GlobalRuntimeProfiler();
		~GlobalRuntimeProfiler();
		
		struct info {
			int calls;
			int timed_calls;
			double total_time;			
		};

		std::unordered_map<std::string, info> m_dataset;
		std::string m_file_name;
		std::mutex write_mutex;
		std::vector< std::unordered_map<std::string, info> > m_timed_dataset;
		std::vector< double > m_timed_dataset_times;
		double m_last_timestamp;
		std::chrono::time_point<std::chrono::steady_clock> m_start;

	public:
		GlobalRuntimeProfiler(GlobalRuntimeProfiler const&) = delete;
		void operator=(GlobalRuntimeProfiler const&) = delete;
	};
}
