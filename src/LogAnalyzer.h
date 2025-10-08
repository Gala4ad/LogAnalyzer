#pragma once
#include "LogEntry.h"

#include <unordered_map>
#include <vector>
#include <iostream>


/**
* @brief ����������� ���-���� ��� ����� ����������.
*/
class LogAnalyzer {
public:

	/**
	* @brief ��������� ������ �� ����� � ������������ ������� �������
	* @param[in] FileName ��� ����� ��� ������.
	* @return 0, ���� ������� �������, ����� 1.
	*/
	bool loadData(const std::string& FileName);

	/**
	* @brief ��������� ������� �� ������� ���������� (�� ��������).
	* @details ������� ������ FunctionByFreq �� ��� (��� �������, ����������) � ��������� ���.
	* @note ������ ���� ������ ����� LoadData.
	*/
	void sortFunctions();

	/**
	* @brief ������� ����� ����������.
	* @details ������� ����� ���������� ������� � ��� ������� � �� ��������.
	*/
	void getStatistic();

	/**
	* @brief ������� N �������� ������ �������. (�� ��������� 10)
	* @param[in] N ���������� ������� ��� ������.
	*/
	void getTopFunctions(int N = 10);

private:
	int nEntries;  ///< ����� ���������� ������� � ���-�����
	std::string fileName;  ///< ��� ���-�����

	std::unordered_map<std::string, int> funcCount; ///< ������� �������
	std::vector<std::pair<std::string, int>> functionByFreq;  ///< ������� ��������������� �� �������
};