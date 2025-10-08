#pragma once
#include "LogEntry.h"

#include <unordered_map>
#include <vector>
#include <iostream>


/**
* @brief Анализирует лог-Файл для сбора статистики.
*/
class LogAnalyzer {
public:

	/**
	* @brief Загружает данные из файла и подсчитывает частоту функций
	* @param[in] FileName Имя файла для чтения.
	* @return 0, если парсинг успешен, иначе 1.
	*/
	bool loadData(const std::string& FileName);

	/**
	* @brief Сортирует функции по частоте упоминаний (по убыванию).
	* @details Создает вектор FunctionByFreq из пар (имя функции, количество) и сортирует его.
	* @note Должен быть вызван после LoadData.
	*/
	void sortFunctions();

	/**
	* @brief Выводит общую статистику.
	* @details Выводит общее количество записей и все функции с их частотой.
	*/
	void getStatistic();

	/**
	* @brief Выводит N наиболее частых функций. (по умолчанию 10)
	* @param[in] N Количество функций для вывода.
	*/
	void getTopFunctions(int N = 10);

private:
	int nEntries;  ///< Общее количество записей в лог-файле
	std::string fileName;  ///< Имя лог-файла

	std::unordered_map<std::string, int> funcCount; ///< Счетчик функций
	std::vector<std::pair<std::string, int>> functionByFreq;  ///< Функции отсортированные по частоте
};