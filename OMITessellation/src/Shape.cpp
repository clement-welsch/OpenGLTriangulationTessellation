#include "Shape.h"
#include <fstream>
#include <sstream>

Shape::Shape(const std::string& _filePath)
{
	
	std::ifstream infile(_filePath, std::ifstream::binary);
	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float value;
		if (iss >> value)
		{
			m_listVertex.push_back(value);

			if (m_listVertex.size() % 2 == 0)
			{
				m_listIndex.push_back(m_listIndex.size());
			}
		}
	}
}