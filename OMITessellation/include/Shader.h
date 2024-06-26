#pragma once
#include <string>
#include <unordered_map>

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
	unsigned int GetRendererID() const { return m_rendererID; }

private:
	ShaderSources ParseShader(const std::string& _filePath);
	const std::string& ParseShader(const std::string& _filePath, const ShaderType _shaderType);
	unsigned int CompileShader(unsigned int _type, const std::string& _source);
	unsigned int CreateShader(const std::string& _vertexShader, const std::string& _fragmentShader);

	int GetUniformLocation(const std::string& _name);

	unsigned int m_rendererID;
	std::string m_filePath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
};