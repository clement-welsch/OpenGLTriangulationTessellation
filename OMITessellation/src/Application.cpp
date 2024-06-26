#include <iostream>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Shape.h"

const static std::string s_smallShapeFilePath = "res\\json\\small.json";
const static std::string s_squareShapeFilePath = "res\\json\\square.json";
const static std::string s_cShapeFilePath = "res\\json\\c.json";
const static std::string s_infiniteShapeFilePath = "res\\json\\infinite.json";
const static std::string s_chaosShapeFilePath = "res\\json\\chaos.json";

const static std::string s_vertexShaderPath = "res\\shader\\Basic.vs";
const static std::string s_fragmentShaderPath = "res\\shader\\Basic.fs";
const static std::string s_shaderPath = "res\\shader\\Basic.shader";

static double s_ortho = 10.0f;

static std::string GetWorkingDir()
{
	char buf[MAX_PATH];
	GetCurrentDirectoryA(256, buf);
	return std::string(buf) + '\\';
}

const static std::string s_dirPath = GetWorkingDir().c_str();

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

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//---Shape

	//Select JSON File
	std::cout << "Choose which file to open by typing the index related to it :" << std::endl;
	std::cout << "1-Small Square shape" << std::endl;
	std::cout << "2-Big Square shape" << std::endl;
	std::cout << "3-C shape" << std::endl;
	std::cout << "4-infinite shape" << std::endl;
	std::cout << "5-Chaos shape" << std::endl;
	std::cout << "6-Quit" << std::endl;

	std::string line;
	std::getline(std::cin, line);
	std::string fileNameSelected;

	switch (line[0])
	{
		case 49:
			fileNameSelected = s_smallShapeFilePath;
			break;
		case 50:
			fileNameSelected = s_squareShapeFilePath;
			break;
		case 51:
			fileNameSelected = s_cShapeFilePath;
			break;
		case 52:
			fileNameSelected = s_infiniteShapeFilePath;
			break;
		case 53:
			fileNameSelected = s_chaosShapeFilePath;
			break;
		default:
			return 0;
	}

	Shape shape(s_dirPath + fileNameSelected);

	if (shape.m_listVertex.empty())
	{
		std::cout << "The file has not been found or is empty!" << std::endl;
		return -1;
	}

	//---Shape

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/*float positions[] = {
		-0.5f, -0.5f,
		 0.5f,  -0.5f,
		 0.5f, 0.5f,
		 -0.5f, 0.5f,
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};*/

	{
		VertexArray va;
		VertexBuffer vb (&shape.m_listVertex[0], shape.m_listVertex.size() * sizeof(float));
		IndexBuffer ib(&shape.m_listIndex[0], shape.m_listIndex.size());

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//Shader setup
		Shader shader(s_dirPath + s_shaderPath);
		shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);
		
		Renderer renderer;

		while (!glfwWindowShouldClose(window))
		{
			// Clear the screen
			renderer.Clear();
			
			shader.Bind();
			shader.SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

			renderer.Draw(va, ib, shader);

			// Swap buffers
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		ib.Unbind();
		va.Unbind();
		vb.Unbind();
		shader.Unbind();

		// Cleanup VBO
		GLCall(glDeleteVertexArrays(1, &VertexArrayID));
	}
	

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}