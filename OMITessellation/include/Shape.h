#pragma once
#include <vector>
#include <string>
#include "glm.hpp"

struct Shape
{
	Shape(const std::string& _filePath);
	

	std::vector<float> m_listVertex;
	std::vector<int> m_listIndex;

private:
	void genNonSymPlaneUniform(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int div);
	void genPlaneIndTes(const unsigned int _div);
};