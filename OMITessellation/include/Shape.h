#pragma once
#include <limits>
#include <vector>


struct Shape
{
	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;
	float m_xMin = FLT_MAX;
	float m_xMax = FLT_MIN;
	float m_yMin = FLT_MAX;
	float m_yMax = FLT_MIN;
};