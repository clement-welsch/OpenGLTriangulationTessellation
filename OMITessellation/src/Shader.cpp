#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Renderer.h"

const static char* s_vertexShaderPath = "res/shader/vertex.vert";
const static char* s_tessControllerShaderPath = "res/shader/tessellation.tesc";
const static char* s_tessEvaluationShaderPath = "res/shader/tessellation.tese";
const static char* s_fragmentShaderPath = "res/shader/fragment.frag";
//const static std::string s_shaderPath = "res/shader/Basic.shader";

Shader::Shader() : m_rendererID (0)
{
	m_rendererID = CreateShader();
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

void Shader::SetUniformMat4f(const std::string& _name, const glm::mat4& _matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(_name), 1, GL_FALSE, &_matrix[0][0]));
}

std::string Shader::ReadText(const char* textFile)
{
	std::FILE* fp = std::fopen(textFile, "rb");
	if (fp)
	{
		std::string contents;
		std::fseek(fp, 0, SEEK_END);
		contents.resize(std::ftell(fp));
		std::rewind(fp);
		std::fread(&contents[0], 1, contents.size(), fp);
		std::fclose(fp);
		return(contents);
	}
	throw(errno);
}

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

unsigned int Shader::CreateShader()
{
	//Load Files
	std::string vertexCode = ReadText(s_vertexShaderPath);
	std::string tesControlCode = ReadText(s_tessControllerShaderPath);
	std::string tesEvalCode = ReadText(s_tessEvaluationShaderPath);
	std::string fragmentCode = ReadText(s_fragmentShaderPath);
	// create a shader program
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexCode);
	unsigned int tesc = CompileShader(GL_TESS_CONTROL_SHADER, tesControlCode);
	unsigned int tese = CompileShader(GL_TESS_EVALUATION_SHADER, tesEvalCode);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentCode);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, tesc));
	GLCall(glAttachShader(program, tese));
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
	GLCall(glDeleteShader(tesc));
	GLCall(glDeleteShader(tese));
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
