#pragma once
#include <vector>
#include <string>
#include "delaunay.hpp"

struct Patch
{
	Patch() {}
	void AddIndex(int _newIndex)
	{
		if (std::find(m_listIndex.begin(), m_listIndex.end(), _newIndex) == m_listIndex.end())
		{
			m_listIndex.push_back(_newIndex);
			std::sort(m_listIndex.begin(), m_listIndex.end());
		}
	}

	std::vector<int> m_listIndex;
};

struct Shape
{
	Shape(const std::string& _filePath);
	

	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;

private:
	const unsigned int GetIndex(std::vector<delaunay::Point<float>>& _listDelaunayPoints, delaunay::Point<float> _p);
	void DelaunayTriangulation();
};