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

static unsigned int CompileShader(unsigned int _type, const std::string& _source)
{
	const unsigned int id =  glCreateShader(_type);
	const char* src = _source.c_str();
	glShaderSource(id, 1, &src, nullptr);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(CHAR));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile : ";
		switch (_type)
		{
		case GL_VERTEX_SHADER:
			std::cout << "Vertex";
			break;
		case GL_TESS_CONTROL_SHADER:
			std::cout << "Tesselation control";
			break;
		case GL_TESS_EVALUATION_SHADER:
			std::cout << "Tesselation evaluation";
			break;
		case GL_COMPUTE_SHADER:
			std::cout << "Compute";
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "Fragment";
			break;
		}
		std::cout << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
static unsigned int CreateShader(const std::string& _vertexShader, const std::string _fragmentShader)
{
	const unsigned int program = glCreateProgram();
	const unsigned int vs = CompileShader(GL_VERTEX_SHADER, _vertexShader);
	if (vs == 0)
	{
		return 0;
	}

	const unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, _fragmentShader);
	if (fs == 0)
	{
		return 0;
	}

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteProgram(vs);
	glDeleteProgram(fs);

	return program;
}

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

void ReadJSON(const char* _filePath, std::vector<float>& _listPoints)
{
	std::string fullpath = GetWorkingDir() + std::string(_filePath);
	std::ifstream infile(fullpath, std::ifstream::binary);

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float value;
		if (iss >> value)
		{ 
			_listPoints.push_back(value);
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

	std::vector<float> tempListPoints;

	switch (line[0])
	{
	case 49:
		ReadJSON(squareShapeFilePath, tempListPoints);
		break;
	case 50:
		ReadJSON(cShapeFilePath, tempListPoints);
		break;
	case 51:
		ReadJSON(infiniteShapeFilePath, tempListPoints);
		break;
	case 52:
		ReadJSON(chaosShapeFilePath, tempListPoints);
		break;
	default:
		return 0;
	}

	if (tempListPoints.empty())
	{
		std::cout << "The file has not been found or is empty!" << std::endl;
		return -1;
	}

	//create an array of points
	const float* arrayPoints = &tempListPoints[0];
	const unsigned int sizeArray = tempListPoints.size();
	tempListPoints.clear();

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
	glBindBuffer(GL_ARRAY_BUFFER, sizeArray * sizeof(float));
	glBufferData(GL_ARRAY_BUFFER, sizeArray * sizeof(float), arrayPoints, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	const std::string vertexShader = "";
	const std::string fragmentShader = "";
	if (unsigned int program = CreateShader(vertexShader, fragmentShader) == 0)
	{
		std::cout << "Shaders creation or compiling error!" << std::endl;
		return -1;
	}

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

		
		/*glPointSize(3.0);
		glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 0.0f, 0.0f);

			for (Point& point : listPoints)
			{
				glVertex3f(point.x, point.y, 0.0f);
			}

		glEnd();*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}