#include <iostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <windows.h>

const char* squareShapeFilePath = "\\json\\square.json";
const char* cShapeFilePath = "\\json\\c.json";
const char* infiniteShapeFilePath = "\\json\\infinite.json";
const char* chaosShapeFilePath = "\\json\\shape.json";

std::string workingdir()
{
	char buf[256];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

void readJSON(const char* _filePath)
{
	std::string path = workingdir();

	std::ifstream infile(path + std::string(squareShapeFilePath), std::ifstream::binary);

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int a;
		if (iss >> a)
		{ 
			std::getline(infile, line);
			std::istringstream iss(line);
			int b;
			if (iss >> b)
			{
				std::cout<<"a : "<<a<<" | b : "<<b<<std::endl;
			}

		} // error

		// process pair (a,b)
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

	switch (line[0])
	{
	case 49:
		readJSON(squareShapeFilePath);
		break;
	case 50:
		readJSON(cShapeFilePath);
		break;
	case 51:
		readJSON(infiniteShapeFilePath);
		break;
	case 52:
		readJSON(chaosShapeFilePath);
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