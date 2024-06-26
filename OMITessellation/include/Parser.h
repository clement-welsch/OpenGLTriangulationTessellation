#pragma once
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>

#include "Shape.h"

struct Parser
{
	static Shape& ParseShape(const std::string& _filePath)
	{
		Shape shape;
		std::ifstream infile(_filePath, std::ifstream::binary);

		std::string line;
		while (std::getline(infile, line))
		{
			std::istringstream iss(line);
			float value;
			if (iss >> value)
			{
				shape.m_listVertex.push_back(value);

				//xMin-xMax-yMin-yMax
				if (shape.m_listVertex.size() % 2 != 0)
				{
					shape.m_xMin = min(shape.m_xMin, value);
					shape.m_xMax = max(shape.m_xMax, value);
				}
				else
				{
					shape.m_yMin = min(shape.m_yMin, value);
					shape.m_yMax = max(shape.m_yMax, value);
					shape.m_listIndex.push_back(shape.m_listVertex.size()-2);
				}
			}
		}
	}
};