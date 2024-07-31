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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

const static std::string s_squareShapeFilePath = "../res/json/square.json";
const static std::string s_cShapeFilePath = "../res/json/c.json";
const static std::string s_infiniteShapeFilePath = "../res/json/infinite.json";

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		system("pause");
		return -1;
	}

	//---Shapes


	Shape shapeSquare(s_squareShapeFilePath);
	Shape shapeInfinite(s_infiniteShapeFilePath);
	Shape shapeC(s_cShapeFilePath);

	std::vector<Shape> listShapes;

	if (shapeSquare.m_listVertex.empty() || shapeSquare.m_listIndex.empty())
	{
		std::cout << "The file square.json has not been found or is empty!" << std::endl;
	}
	else
	{
		listShapes.push_back(shapeSquare);
	}

	if (shapeInfinite.m_listVertex.empty() || shapeInfinite.m_listIndex.empty())
	{
		std::cout << "The file infinite.json has not been found or is empty!" << std::endl;
	}
	else
	{
		listShapes.push_back(shapeInfinite);
	}

	if (shapeC.m_listVertex.empty() || shapeC.m_listIndex.empty())
	{
		std::cout << "The file c.json has not been found or is empty!" << std::endl;
	}
	else
	{
		listShapes.push_back(shapeC);
	}

	if (listShapes.empty() || listShapes.empty())
	{
		std::cout << "The vector Shape is empty!" << std::endl;
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
		VertexBuffer* vb = new VertexBuffer(&listShapes[0].m_listVertex[0], listShapes[0].m_listVertex.size() * sizeof(float));
		IndexBuffer* ib = new IndexBuffer(&listShapes[0].m_listIndex[0], listShapes[0].m_listIndex.size());

		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(*vb, layout);

		//matrices transformation
		glm::mat4 proj = glm::ortho(-14.0, 14.0, -10.5, 10.5, -1.0, 1.0);

		//Shader setup
		Shader shaderBasic;
		shaderBasic.SetUniformMat4f("u_mvp", proj);
		shaderBasic.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);

		Shader shaderTess(true);
		shaderTess.SetUniformMat4f("u_mvp", proj);
		shaderTess.SetUniform4f("u_color", 0.0f, 1.0f, 0.0f, 1.0f);

		Renderer renderer;

		//ImGUI
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
		const char* glsl_version = "#version 460";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Our state
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		unsigned int shape_counter = 0;

		while (!glfwWindowShouldClose(window))
		{
			// Clear the screen
			renderer.Clear();

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			renderer.Draw(va, *ib, shaderBasic, shaderTess);

			{
				/*static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();*/

				ImGui::Begin("Options");

				if (ImGui::Button("Change Shape"))
				{
					if (vb != nullptr)
					{
						delete vb;
					}

					if (ib != nullptr)
					{
						delete ib;
					}

					shape_counter++;
					if (shape_counter >= listShapes.size())
					{
						shape_counter = 0;
					}

					Shape newShape = listShapes[shape_counter];

					vb = new VertexBuffer(&newShape.m_listVertex[0], newShape.m_listVertex.size() * sizeof(float));
					ib = new IndexBuffer(&newShape.m_listIndex[0], newShape.m_listIndex.size());
					va.AddBuffer(*vb, layout);
				}
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// Swap buffers
			GLCall(glfwSwapBuffers(window));
			GLCall(glfwPollEvents());
		}

		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		ib->Unbind();
		delete ib;
		va.Unbind();
		vb->Unbind();
		delete vb;
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