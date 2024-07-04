#include "Shape.h"
#include <fstream>
#include <sstream>

Shape::Shape(const std::string& _filePath)
{
	unsigned int nbVertex = 0;
	std::ifstream infile(_filePath, std::ifstream::binary);

	bool isVertex = true;
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
				nbVertex++;
			}
		}
	}
	genPlaneIndTes(4);

	//Auto indexing - GL_TRIANGLES
	/*for (int i = 0, j = nbVertex-1; i < (nbVertex-1) /2; i++, j--)
	{
		{
			//T1
			const int p0 = i;
			const int p1 = i + 1;
			const int p2 = j;

			m_listIndex.push_back(p0);
			m_listIndex.push_back(p1);
			m_listIndex.push_back(p2);
		}

		{
			//T2
			const int p0 = i + 1;
			const int p1 = j - 1;
			const int p2 = j;

			m_listIndex.push_back(p0);
			m_listIndex.push_back(p1);
			m_listIndex.push_back(p2);
		}
	}*/

	/*for (int i = 0; i < nbVertex; i++)
	{
		m_listIndex.push_back(i);
	}
	m_listIndex.push_back(0);*/
}

void Shape::genPlaneIndTes(const unsigned int _div)
{
	for (int row = 0; row < _div; row++)
	{
		for (int col = 0; col < _div; col++)
		{
			int index = row * (_div + 1) + col;				// 3___2
			m_listIndex.push_back(index);					//     |
			m_listIndex.push_back(index + 1);				//     |
			m_listIndex.push_back(index + (_div + 1) + 1);	//  ___|
			m_listIndex.push_back(index + (_div + 1));		// 0   1
		}
	}
}