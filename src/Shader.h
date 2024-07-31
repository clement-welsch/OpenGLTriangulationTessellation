#pragma once
#include <string>
#include <unordered_map>
#include "glm.hpp"


class Shader
{
public:
	Shader();
	Shader(const bool _activateTess);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//set uniforms
	void SetUniform1f(const std::string& _name, float _value);
	void SetUniform4f(const std::string& _name, float _v0, float _v1, float _v2, float _v3);
	void SetUniformMat4f(const std::string& _name, const glm::mat4& _matrix);
	unsigned int GetRendererID() const { return m_rendererID; }

private:
	std::string ReadText(const char* textFile);
	unsigned int CompileShader(unsigned int _type, const std::string& _source);
	unsigned int CreateBasicShader();
	unsigned int CreateTessellationShader();
	int GetUniformLocation(const std::string& _name);

	unsigned int m_rendererID;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};