#include "Shape.h"
#include <fstream>
#include <sstream>

Shape::Shape(const std::string& _filePath)
{
	unsigned int nbVertex = 0;
	std::ifstream infile(_filePath, std::ifstream::binary);

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float value;
		if (iss >> value)
		{
			m_listVertex.push_back(value);

			//xMin-xMax-yMin-yMax
			if (m_listVertex.size() % 2 != 0)
			{
				m_xMin = std::min(m_xMin, value);
				m_xMax = std::max(m_xMax, value);
			}
			else
			{
				m_yMin = std::min(m_yMin, value);
				m_yMax = std::max(m_yMax, value);
				m_listIndex.push_back(nbVertex++);

				if (nbVertex % 2 == 0)
				{
					m_listIndex.push_back(nbVertex);
				}
			}
		}
	}
	m_listIndex[m_listIndex.size()-1] = 0;
}