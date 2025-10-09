#pragma once
#include <string>
#include <chrono>
#include <iostream>

/**
* @brief Хранит распарсенную строку.
*/
struct LogEntry {
	std::chrono::system_clock::time_point timestamp; ///< Дата и время.
	int thread_id; ///< идентификатор потока-выполнения.
	std::string log_level; ///< Уровень логирования.
	std::string function; ///< Имя вызываемой функции или блока кода.
	std::string payload; ///< Произвольный текст.
};
