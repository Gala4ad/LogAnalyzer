#include "log_line_parser.h"

#include <sstream>
#include <iomanip>


//Ожидает формат: ГГГГ-ММ-ДД ЧЧ:ММ:СС.микросекунды]
std::optional<std::chrono::system_clock::time_point> LogParser::ParseDate(const std::string& date) {
	std::tm tm = {};
	std::stringstream ss(date);

	ss >> std::get_time(&tm, "%Y %m %d %H:%M:%S");
	if (ss.fail()) {
		return std::nullopt;
	}

	auto time = std::chrono::system_clock::from_time_t(std::mktime(&tm));

	//Обработка микросекунд
	size_t dot_pos = date.find('.');
	if (dot_pos != std::string::npos) {
		try {
			int microseconds = std::stoi(date.substr(dot_pos + 1));
			time += std::chrono::microseconds(microseconds);
		}
		catch (const std::invalid_argument&) {
			return std::nullopt;
		}
	}

	return time;
}

//Ожидает формат строки: "[timestamp] [thread_id] <log_level> function_name payload_message
std::optional<LogEntry> LogParser::ParseLogLine(const std::string& line) {
	LogEntry Entry;

	size_t start_pos = 0;
	size_t end_pos = 0;

	//Parse timestamp
	start_pos = line.find('[');
	end_pos = line.find(']', start_pos);
	if (end_pos == std::string::npos)
		return std::nullopt;

	std::string time_stamp = line.substr(start_pos + 1, end_pos - start_pos - 1);
	auto parsed_date = LogParser::ParseDate(time_stamp);
	if (parsed_date)
		Entry.timestamp = (*parsed_date);

	//Parse thread id
	start_pos = line.find('[', end_pos);
	end_pos = line.find(']', start_pos);
	if (end_pos == std::string::npos)
		return std::nullopt;

	std::string thread = line.substr(start_pos + 1, end_pos - start_pos - 1);
	try {
		Entry.thread_id = std::stoi(thread);
	}
	catch (const std::invalid_argument&) {
		return std::nullopt;
	}

	//parse log level
	start_pos = line.find('<', end_pos);
	end_pos = line.find('>', start_pos);
	if (end_pos == std::string::npos)
		return std::nullopt;

	Entry.log_level = line.substr(start_pos + 1, end_pos - start_pos - 1);


	//parse function & payload
	start_pos = end_pos + 1;
	if (start_pos > line.length())
		return std::nullopt;

	start_pos = line.find_first_not_of(' ', start_pos);
	if (start_pos == std::string::npos)
		return std::nullopt;

	end_pos = line.find(' ', start_pos);
	if (end_pos == std::string::npos) {
		Entry.function = line.substr(start_pos);
	}
	else {
		Entry.function = line.substr(start_pos, end_pos - start_pos);

		//parse payload
		start_pos = line.find_first_not_of(' ', end_pos);
		Entry.payload = line.substr(start_pos);
	}

	return Entry;
}