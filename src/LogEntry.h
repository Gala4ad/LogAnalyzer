#pragma once
#include <string>
#include <chrono>
#include <iostream>


struct LogEntry {
	std::chrono::system_clock::time_point timestamp;
	int thread_id;
	std::string log_level; 
	std::string function; 
	std::string payload; 
};
