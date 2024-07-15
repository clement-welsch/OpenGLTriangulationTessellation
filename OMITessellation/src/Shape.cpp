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
		}
	}
	
	DelaunayTriangulation();
}

const unsigned int Shape::GetIndex(std::vector<delaunay::Point<float>>& _listDelaunayPoints, delaunay::Point<float> _p)
{
	auto it = find(_listDelaunayPoints.begin(), _listDelaunayPoints.end(), _p);
 
	if (it != _listDelaunayPoints.end())
	{
		const unsigned int index = it - _listDelaunayPoints.begin();
		return index;
	}
	else
	{
		return -1;
	}
}

const bool IsNeighboursTriangle(delaunay::Triangle<float> _t1, delaunay::Triangle<float> _t2)
{
	const bool e00 = _t1.e0 == _t2.e0;
	const bool e01 = _t1.e0 == _t2.e1;
	const bool e02 = _t1.e0 == _t2.e2;

	const bool e10 = _t1.e1 == _t2.e0;
	const bool e11 = _t1.e1 == _t2.e1;
	const bool e12 = _t1.e1 == _t2.e2;

	const bool e20 = _t1.e2 == _t2.e0;
	const bool e21 = _t1.e2 == _t2.e1;
	const bool e22 = _t1.e2 == _t2.e2;

	if (e00 || e01 || e02 || e10 || e11 || e12 || e20 || e21 || e22)
	{
		return true;
	}
	
	return false;
}

int GetAngleABC(delaunay::Point<float> a, delaunay::Point<float> b, delaunay::Point<float> c)
{
	const float pi = 3.141592f;

	delaunay::Point<float> ab = { b.x - a.x, b.y - a.y };
	delaunay::Point<float> cb = { b.x - c.x, b.y - c.y };

	float dot = (ab.x * cb.x + ab.y * cb.y); // dot product
	float cross = (ab.x * cb.y - ab.y * cb.x); // cross product

	float alpha = atan2(cross, dot);

	return (int)floor(alpha * 180. / pi + 0.5);
}

const bool CheckPatch(delaunay::Point<float>& _p0, delaunay::Point<float>& _p1, delaunay::Point<float>& _p2, delaunay::Point<float>& _p3)
{
	const int angle1 = abs(GetAngleABC(_p0, _p1, _p2));
	const int angle2 = abs(GetAngleABC(_p1, _p2, _p3));
	const int angle3 = abs(GetAngleABC(_p2, _p3, _p0));
	const int angle4 = abs(GetAngleABC(_p3, _p0, _p1));

	const int result = angle1 + angle2 + angle3 + angle4;

	if (result > 280)
	{
		return true;
	}
	return false;
}

void Shape::DelaunayTriangulation()
{
	std::vector<delaunay::Point<float>> points;

	for (int i = 0; i < m_listVertex.size(); i += 2)
	{
		points.push_back(delaunay::Point<float>(m_listVertex[i], m_listVertex[i + 1]));
	}

	const auto triangulation = delaunay::triangulate(points);

	std::vector<void*> vectorTrianglesUsed;
	std::vector<Patch> vectorPatches;

	for (auto const& t1 : triangulation.triangles)
	{
		for (auto const& t2 : triangulation.triangles)
		{
			const bool alreadyUsed = std::find(vectorTrianglesUsed.begin(), vectorTrianglesUsed.end(), &t2) != vectorTrianglesUsed.end();

			if (&t1 == &t2 || alreadyUsed)
			{
				continue;
			}

			const bool isNeighbours = IsNeighboursTriangle(t1, t2);
			
			if (isNeighbours)
			{	
				Patch p;

				p.AddIndex(GetIndex(points, t1.p0));
				p.AddIndex(GetIndex(points, t1.p1));
				p.AddIndex(GetIndex(points, t1.p2));

				p.AddIndex(GetIndex(points, t2.p0));
				p.AddIndex(GetIndex(points, t2.p1));
				p.AddIndex(GetIndex(points, t2.p2));

				const bool check = CheckPatch(points[p.m_listIndex[0]], points[p.m_listIndex[1]], points[p.m_listIndex[2]], points[p.m_listIndex[3]]);
				if (check)
				{
					vectorPatches.push_back(p);
					break;
				}
			}
		}
		vectorTrianglesUsed.push_back((void*)&t1);
	}
	
	for (int i = 0; i < vectorPatches.size(); i++)
	{
		Patch p = vectorPatches[i];

		for (int j = 0; j < p.m_listIndex.size(); j++)
		{
			m_listIndex.push_back(p.m_listIndex[j]);
		}
	}
	
	points.clear();
	vectorPatches.clear();
	vectorTrianglesUsed.clear();
}
