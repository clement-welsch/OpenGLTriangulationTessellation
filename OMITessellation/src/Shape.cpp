#include "Shape.h"
#include <fstream>
#include <sstream>

Shape::Shape(const std::string& _filePath)
{
	
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

			
		}
	}
	DelaunayTriangulation();
}

const unsigned int Shape::GetIndex(std::vector<delaunay::Point<float>>& _listDelaunayPoints, delaunay::Point<float> _p)
{
	auto it = find(_listDelaunayPoints.begin(), _listDelaunayPoints.end(), _p);

	// If element was found 
	if (it != _listDelaunayPoints.end())
	{

		// calculating the index 
		// of K 
		const unsigned int index = it - _listDelaunayPoints.begin();
		return index;
	}
	else
	{
		return -1;
	}
}

void Shape::DelaunayTriangulation()
{
	std::vector<delaunay::Point<float>> points;

	for (int i = 0; i < m_listVertex.size(); i += 2)
	{
		points.push_back(delaunay::Point<float>(m_listVertex[i], m_listVertex[i + 1]));
	}

	const auto triangulation = delaunay::triangulate(points);

	//find points in the list
	for (auto const& triangle : triangulation.triangles)
	{
		const unsigned int i0 = GetIndex(points, triangle.p0);
		const unsigned int i1 = GetIndex(points, triangle.p1);
		const unsigned int i2 = GetIndex(points, triangle.p2);

		m_listIndex.push_back(i0);
		m_listIndex.push_back(i1);
		m_listIndex.push_back(i2);
	}
}
