#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Renderer.h"

enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderSources
{
	std::string vertexSource;
	std::string fragmentSource;
};

Shader::Shader(const std::string& _filePath) : m_filePath (_filePath), m_rendererID (0)
{
	ShaderSources source = ParseShader(m_filePath);
	m_rendererID = CreateShader(source.vertexSource, source.fragmentSource);
	GLCall(glUseProgram(m_rendererID));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_rendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_rendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& _name, float _v0, float _v1, float _v2, float _v3)
{
	GLCall(glUniform4f(GetUniformLocation(_name), _v0, _v1, _v2, _v3));
}

void Shader::SetUniformMat4f(const std::string& _name, const glm::mat4 _matrix)
{
}

ShaderSources Shader::ParseShader(const std::string& _filePath)
{
	std::ifstream stream(_filePath);

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str() };
}

/*const std::string& Shader::ParseShader(const std::string& _filePath, const ShaderType _shaderType)
{
	std::string input;
	std::cin >> input;
	std::ofstream out(_filePath);
	out << input;
	out.close();
	return input;
}*/

unsigned int Shader::CompileShader(unsigned int _type, const std::string& _source)
{
	GLCall(unsigned int id = glCreateShader(_type));
	const char* src = _source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
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
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& _vertexShader, const std::string& _fragmentShader)
{
	// create a shader program
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, _vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, _fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));

	GLCall(glLinkProgram(program));

	GLint program_linked;

	GLCall(glGetProgramiv(program, GL_LINK_STATUS, &program_linked));
	std::cout << "Program link status: " << program_linked << std::endl;
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		GLCall(glGetProgramInfoLog(program, 1024, &log_length, message));
		std::cout << "Failed to link program" << std::endl;
		std::cout << message << std::endl;
	}

	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

int Shader::GetUniformLocation(const std::string& _name)
{
	if (m_uniformLocationCache.find(_name) != m_uniformLocationCache.end())
	{
		return m_uniformLocationCache[_name];
	}

	GLCall(int location = glGetUniformLocation(m_rendererID, _name.c_str()));
	if (location == -1)
	{
		std::cout << " Warning uniform '" << _name << "' doesn't exist!" << std::endl;
	}

	m_uniformLocationCache[_name] = location;

	return location;
}
