#pragma once
#include "LogEntry.h"

#include <optional>

class LogParser {
public:

	static std::optional<std::chrono::system_clock::time_point> ParseDate(const std::string& date);

	static std::optional<LogEntry> ParseLogLine(const std::string& line);
};



