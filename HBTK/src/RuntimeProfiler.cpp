#include "RuntimeProfiler.h"
/*////////////////////////////////////////////////////////////////////////////
RuntimeProfiler.cpp

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


#include <fstream>

HBTK::GlobalRuntimeProfiler::GlobalRuntimeProfiler()
	: m_file_name("runtime_profile.out")
{
}

HBTK::GlobalRuntimeProfiler::~GlobalRuntimeProfiler()
{
	try {
		std::ofstream output(m_file_name);
		new_timeset_now();
		int i = (int)m_timed_dataset.size();
		for (int j = 0; j < i; j++) {
			output << m_timed_dataset_times[j] << '\n';
			auto& dataset = m_timed_dataset[j];
			for (auto &record : dataset) {
				output << '\t' << record.first << ": "
					<< record.second.calls << " "
					<< record.second.timed_calls << " "
					<< record.second.total_time << " "
					<< record.second.total_time / record.second.timed_calls << "\n";
			}
		}
	}
	catch (...) { 
		// This is a destructor, so terminations are not what we want!
		;
	}
}

HBTK::GlobalRuntimeProfiler & HBTK::GlobalRuntimeProfiler::get_instance()
{
	static GlobalRuntimeProfiler instance;
	return instance;
}

void HBTK::GlobalRuntimeProfiler::set_file(std::string file_name)
{
	get_instance().m_file_name = file_name;
}

void HBTK::GlobalRuntimeProfiler::new_timeset_now()
{
	auto& inst = GlobalRuntimeProfiler::get_instance();
	inst.write_mutex.lock();
	inst.m_timed_dataset.push_back(inst.m_dataset);
	inst.m_timed_dataset_times.push_back(inst.m_last_timestamp);
	auto end = std::chrono::steady_clock::now();
	inst.m_last_timestamp = std::chrono::duration<double, std::nano>(end - inst.m_start).count();
	inst.m_dataset.clear();
	inst.write_mutex.unlock();
}

HBTK::RuntimeProfiler::RuntimeProfiler(const char * function, const int line_no)
	: m_timing(false),
	m_string(std::to_string(line_no) + ' ' + std::string(function))
{

}

HBTK::RuntimeProfiler::RuntimeProfiler(const char * function, const int line_no, const bool timing)
	: m_timing(timing),
	m_string(std::to_string(line_no) + ' ' + std::string(function))
{
	if (timing) {
		t_start = std::chrono::steady_clock::now();
	}
}

HBTK::RuntimeProfiler::~RuntimeProfiler()
{
	std::chrono::time_point<std::chrono::steady_clock> end;
	double time;
	if (m_timing) {
		end = std::chrono::steady_clock::now();
		time = std::chrono::duration<double, std::nano>(end - t_start).count();
	}
	auto& inst = GlobalRuntimeProfiler::get_instance();
	inst.write_mutex.lock();
	if (!inst.m_dataset.count(m_string)) {
		auto& tmp = inst.m_dataset[m_string];
		tmp.calls = 1;
		if (!m_timing) {
			tmp.timed_calls = 0;
			tmp.total_time = 0;
		}
		else {
			tmp.timed_calls = 1;
			tmp.total_time = time;
		}
	}
	else {
		auto& tmp = inst.m_dataset[m_string];
		tmp.calls += 1;
		if (m_timing) {
			tmp.timed_calls += 1;
			tmp.total_time = tmp.total_time + time;
		}
	}
	inst.write_mutex.unlock();
}
