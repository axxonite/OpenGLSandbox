#pragma once

#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat4(const std::string& name, float x, float y, float z, float w) const;

private:
	
	unsigned int id_;

	int createShader(const char* source, unsigned int shaderType, const char* errorType);

};