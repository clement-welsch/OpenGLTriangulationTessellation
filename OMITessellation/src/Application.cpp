#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <vector>

const char* squareShapeFilePath = "json\\square.json";
const char* cShapeFilePath = "json\\c.json";
const char* infiniteShapeFilePath = "json\\infinite.json";
const char* chaosShapeFilePath = "json\\chaos.json";

struct Point
{
	Point(float _x, float _y) : x(_x), y(_y) {}
	float x = 0.0f;
	float y = 0.0f;
};

std::string GetWorkingDir()
{
	char buf[MAX_PATH];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& _horizontal, int& _vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	_horizontal = desktop.right;
	_vertical = desktop.bottom;
}

void ReadJSON(const char* _filePath, std::vector<Point>& _listPoints)
{
	std::string fullpath = GetWorkingDir() + std::string(_filePath);
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
				_listPoints.push_back(Point(x, y));
			}

		}
	}
}

static void key_callback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
	if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(_window, GL_TRUE);
	}
}

static void error_callback(int _error, const char* _description)
{
	fputs(_description, stderr);
}

int main()
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		std::cout << "OpenGL is not available on your device!" << std::endl;
		return -1;
	}

	//Select JSON File
	std::cout << "Choose which file to open by typing the index related to it :" << std::endl;
	std::cout << "1-Square shape" << std::endl;
	std::cout << "2-C shape" << std::endl;
	std::cout << "3-infinite shape" << std::endl;
	std::cout << "4-Chaos shape" << std::endl;
	std::cout << "5-Quit" << std::endl;

	std::string line;
	std::getline(std::cin, line);

	std::vector<Point> listPoints;

	switch (line[0])
	{
	case 49:
		ReadJSON(squareShapeFilePath, listPoints);
		break;
	case 50:
		ReadJSON(cShapeFilePath, listPoints);
		break;
	case 51:
		ReadJSON(infiniteShapeFilePath, listPoints);
		break;
	case 52:
		ReadJSON(chaosShapeFilePath, listPoints);
		break;
	default:
		return 0;
	}

	if (listPoints.empty())
	{
		std::cout << "The file has not been found or is empty!" << std::endl;
		return -1;
	}

	//Viewport Dimenssions
	int width = 0;
	int height = 0;
	GetDesktopResolution(width, height);

	window = glfwCreateWindow(width / 2, height / 2, "Draw Polygons", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW was not initialized properly!" << std::endl;
		return -1;
	}

	unsigned int buffer;
	glGenBuffers(1, &buffer);

	//Render
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10.0 * ratio, 10.0 * ratio, -10.0, 10.0, 10.0, -10.0);
		glMatrixMode(GL_MODELVIEW);

		glPointSize(3.0);
		glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);

			for (Point& point : listPoints)
			{
				glVertex3f(point.x, point.y, 0.0f);
			}

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}