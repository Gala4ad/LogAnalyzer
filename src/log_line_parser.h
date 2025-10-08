#pragma once
#include "LogEntry.h"

#include <optional>

/**
* @brief ������ ������ ���-�����.
*/
class LogParser {
public:

	/**
	* @brief ������ ������ � ����� � ��������.
	* @param date ������ � ����� � ��������.
	* @return ������ time_point, ���� ������� �������, ����� std::nullopt.
	*/
	static std::optional<std::chrono::system_clock::time_point> ParseDate(const std::string& date);

	/**
	* @brief ������ ������ ���-�����
	* @param line ������ ���-�����.
	* @return ������ LogEntry, ���� ������� �������, ����� std::nullopt.
	*/
	static std::optional<LogEntry> ParseLogLine(const std::string& line);
};



