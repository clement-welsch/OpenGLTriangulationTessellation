#include "Shape.h"
#include <fstream>
#include <sstream>
#include <earcut.hpp>
#include <array>

Shape::Shape(const std::string& _filePath)
{
	//Ear clipping triangulation
	using Coord = double;
	using N = uint32_t;
	using Point = std::array<Coord, 2>;
	std::vector<std::vector<std::array<Coord, 2>>> polygon;


	std::ifstream infile(_filePath, std::ifstream::binary);
	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float value;
		if (iss >> value)
		{
			m_listVertex.push_back(value);
			const unsigned size = m_listVertex.size();

			if (size % 2 == 0)
			{
				polygon.push_back({ {m_listVertex[size - 2], m_listVertex[size - 1]} });
			}
		}
	}
	std::vector<N> indices = mapbox::earcut<N>(polygon);
	m_listIndex = std::copy(vect1.begin(), vect1.end(), back_inserter(vect2));
}