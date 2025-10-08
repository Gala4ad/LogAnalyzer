#pragma once
#include "LogEntry.h"

#include <optional>

/**
* @brief Парсит строку лог-файла.
*/
class LogParser {
public:

	/**
	* @brief Парсит строку с датой и временем.
	* @param date Строка с датой и временем.
	* @return Объект time_point, если парсинг успешен, иначе std::nullopt.
	*/
	static std::optional<std::chrono::system_clock::time_point> ParseDate(const std::string& date);

	/**
	* @brief Парсит строку лог-файла
	* @param line строка лог-файла.
	* @return Объект LogEntry, если парсинг успешен, иначе std::nullopt.
	*/
	static std::optional<LogEntry> ParseLogLine(const std::string& line);
};



