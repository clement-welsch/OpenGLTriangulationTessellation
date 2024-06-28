#pragma once
#include <string>
#include <unordered_map>
#include "glm.hpp"

struct ShaderSources;

class Shader
{
public:
	Shader(const std::string& _filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform4f(const std::string& _name, float _v0, float _v1, float _v2, float _v3);
	void SetUniformMat4f(const std::string& _name, const glm::mat4 _matrix);
	unsigned int GetRendererID() const { return m_rendererID; }

private:
	ShaderSources ParseShader(const std::string& _filePath);
	unsigned int CompileShader(unsigned int _type, const std::string& _source);
	unsigned int CreateShader(const std::string& _vertexShader, const std::string& _fragmentShader);

	int GetUniformLocation(const std::string& _name);

	unsigned int m_rendererID;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};