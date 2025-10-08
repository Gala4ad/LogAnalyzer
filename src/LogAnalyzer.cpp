#include "LogAnalyzer.h"
#include "log_line_parser.h"

#include <charconv>
#include <sstream>
#include <fstream>
#include <istream>
#include <iomanip>
#include <algorithm>

bool LogAnalyzer::loadData(const std::string& fileName) {

	std::ifstream inFile(fileName.c_str());
	if (!inFile.is_open()) {
		std::cerr << "Error opening file" << std::endl;

		return 1;
	}

	std::string line;
	nEntries = 0;

	while (std::getline(inFile, line)) {

		if(auto Parsed_Line = LogParser::ParseLogLine(line)){
			if ((*Parsed_Line).function != "-") {
				nEntries++;
				funcCount[(*Parsed_Line).function]++;
			}
		}
	}

	inFile.close();

	return 0;
}


void LogAnalyzer::sortFunctions() {

	//Store Functions in vector<pair<string, int>> and sort it
	functionByFreq.resize(funcCount.size());

	size_t i = 0;
	for (auto el : funcCount) {
		functionByFreq[i] = {el.first, el.second};
		i++;
	}

	auto compareByFrequency = [](const auto& a, const auto& b){
		return a.second > b.second;
	};

	std::sort(functionByFreq.begin(), functionByFreq.end(), compareByFrequency);
}

void LogAnalyzer::getStatistic() {

	std::cout << std::endl;
	std::cout << "Total amount of entries: " << nEntries << std::endl;
	std::cout << std::endl;
	std::cout << "Number of entries by function: " << std::endl;

	for (auto i: functionByFreq)
		std::cout << i.first << " " << i.second << std::endl;

	std::cout << std::endl;
}

void LogAnalyzer::getTopFunctions(int N) {

	std::cout << std::endl;
	if (functionByFreq.empty()) {
		std::cout << "Functions in log file not foound " << std::endl;
		return;
	}

	if (N <= 0) {
		std::cout << "N must be positive. Using default value 10." << std::endl;
		std::cout << std::endl;
		N = 10;
	}

	size_t N_actual = std::min(static_cast<size_t>(N), functionByFreq.size());

	if (N_actual < N) {
		std::cout << "Only " << N_actual << " unique functions found in log:" << std::endl;
	}
	else {
		std::cout << "Top " << N_actual << " functions:" << std::endl;
	}

	for (size_t i = 0; i < N_actual; i++)
		std::cout << functionByFreq[i].first << ": " << functionByFreq[i].second << std::endl;
}

