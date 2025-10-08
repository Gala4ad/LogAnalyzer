#pragma once
#include "LogEntry.h"

#include <unordered_map>
#include <vector>
#include <iostream>


class LogAnalyzer {
public:

	bool loadData(const std::string& FileName);

	void sortFunctions();

	void getStatistic();

	void getTopFunctions(int N = 10);

private:
	int nEntries; 
	std::string fileName;  

	std::unordered_map<std::string, int> funcCount;
	std::vector<std::pair<std::string, int>> functionByFreq;
};