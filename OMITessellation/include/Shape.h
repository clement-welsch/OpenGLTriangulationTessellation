#pragma once
#include <vector>
#include <string>

struct Shape
{
	Shape(const std::string& _filePath);

	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;
	double m_xMin = FLT_MAX;
	double m_xMax = FLT_MIN;
	double m_yMin = FLT_MAX;
	double m_yMax = FLT_MIN;
};