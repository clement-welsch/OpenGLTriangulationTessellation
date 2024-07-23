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

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

const static std::string s_squareShapeFilePath = "res/json/square.json";
const static std::string s_cShapeFilePath = "res/json/c.json";
const static std::string s_infiniteShapeFilePath = "res/json/infinite.json";
const static std::string s_chaosShapeFilePath = "res/json/chaos.json";

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		system("pause");
		return -1;
	}

	//---Shape
	std::string fileNameSelected;

	//Select JSON File
	std::cout << "Choose which file to open by typing the index related to it :" << std::endl;
	std::cout << "1-Big Square shape" << std::endl;
	std::cout << "2-infinite shape" << std::endl;
	std::cout << "3-C shape" << std::endl;
	std::cout << "4-Chaos shape" << std::endl;
	std::cout << "5-Quit" << std::endl;

	std::string line;
	std::getline(std::cin, line);

	switch (line[0])
	{
		case 49:
			fileNameSelected = s_squareShapeFilePath;
			break;
		case 50:
			fileNameSelected = s_infiniteShapeFilePath;
			break;
		case 51:
			fileNameSelected = s_cShapeFilePath;
			break;
		case 52:
			fileNameSelected = s_chaosShapeFilePath;
			break;
		default:
			return 0;
	}

	//fileNameSelected = s_squareShapeFilePath;
	Shape shape(fileNameSelected);

	if (shape.m_listVertex.empty() || shape.m_listIndex.empty())
	{
		std::cout << "The file has not been found or is empty!" << std::endl;
		system("pause");
		return -1;
	}

	//Setup GLFW

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(1024, 768, "Ear Clipping Triangulation & Tessellation", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		glfwTerminate();
		system("pause");
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
		system("pause");
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

	{
		VertexArray va;
		VertexBuffer vb (&shape.m_listVertex[0], shape.m_listVertex.size() * sizeof(float));
		IndexBuffer ib(&shape.m_listIndex[0], shape.m_listIndex.size());

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//matrices transformation
		glm::mat4 proj = glm::ortho(-14.0, 14.0, -10.5, 10.5, -1.0, 1.0);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

		//Shader setup
		Shader shaderBasic;
		shaderBasic.SetUniformMat4f("u_mvp", proj);
		shaderBasic.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);

		Shader shaderTess(true);
		shaderTess.SetUniformMat4f("u_mvp", proj);
		shaderTess.SetUniform4f("u_color", 0.0f, 1.0f, 0.0f, 1.0f);

		Renderer renderer;

		while (!glfwWindowShouldClose(window))
		{
			// Clear the screen
			renderer.Clear();
			renderer.Draw(va, ib, shaderBasic, shaderTess);

			// Swap buffers
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		ib.Unbind();
		va.Unbind();
		vb.Unbind();
		shaderBasic.Unbind();
		shaderTess.Unbind();

		// Cleanup VBO
		GLCall(glDeleteVertexArrays(1, &VertexArrayID));
	}
	

	// Close OpenGL window and terminate GLFW
	glfwTerminate();
	system("pause");
	return 0;
}