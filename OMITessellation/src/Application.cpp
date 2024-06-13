#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>

const char* squareShapeFilePath = "json\\square.json";
const char* cShapeFilePath = "json\\c.json";
const char* infiniteShapeFilePath = "json\\infinite.json";
const char* chaosShapeFilePath = "json\\chaos.json";

struct vec2
{
	vec2(float _x, float _y) : x(_x), y(_y) {}
	float x = 0.0f;
	float y = 0.0f;
};

std::string workingdir()
{
	char buf[MAX_PATH];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

void readJSON(const char* _filePath, std::vector<vec2>& _listVec2)
{
	std::string fullpath = workingdir() + std::string(_filePath);
	std::ifstream infile(fullpath, std::ifstream::binary);

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float x;
		if (iss >> x)
		{ 
			std::getline(infile, line);
			std::istringstream iss(line);
			float y;
			if (iss >> y)
			{
				std::cout<<"x : "<<x<<" | y : "<<y<<std::endl;
				_listVec2.push_back(vec2(x, y));
			}

		}
	}
}

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return -1;
	}

	std::cout << "Choose which file to open by typing the index related to it :" << std::endl;
	std::cout << "1-Square shape" << std::endl;
	std::cout << "2-C shape" << std::endl;
	std::cout << "3-infinite shape" << std::endl;
	std::cout << "4-Chaos shape" << std::endl;
	std::cout << "5-Quit" << std::endl;

	std::string line;
	std::getline(std::cin, line);

	std::vector<vec2> listVec2;

	switch (line[0])
	{
	case 49:
		readJSON(squareShapeFilePath, listVec2);
		break;
	case 50:
		readJSON(cShapeFilePath, listVec2);
		break;
	case 51:
		readJSON(infiniteShapeFilePath, listVec2);
		break;
	case 52:
		readJSON(chaosShapeFilePath, listVec2);
		break;
	default:
		return 0;
	}

	window = glfwCreateWindow(640, 480, "Hello World!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}