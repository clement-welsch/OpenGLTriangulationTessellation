#pragma once
#include <vector>
#include <string>

struct Shape
{
	Shape(const std::string& _filePath);
	

	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;
};