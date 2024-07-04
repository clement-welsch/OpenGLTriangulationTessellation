#pragma once
#include <vector>
#include <string>
#include "delaunay.hpp"

struct Shape
{
	Shape(const std::string& _filePath);
	

	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;

private:
	const unsigned int GetIndex(std::vector<delaunay::Point<float>>& _listDelaunayPoints, delaunay::Point<float> _p);
	void DelaunayTriangulation();
};