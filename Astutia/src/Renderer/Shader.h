#pragma once
#include "glm.hpp"
#include <string>

class Shader {
public:
	Shader(std::string fs = "res/shader/fs.shader", std::string vs = "res/shader/vs.shader");
	~Shader();

	void bind() const;
	void unbind() const;
	void setUniform1i(const char* name, const int value) const;
	void setUniform1f(const char* name, const float value) const;
	void setUniform3f(const char* name, const float v1, const float v2, const float v3) const;
	void setUniform3fv(const char* name, const glm::vec3 value) const;

	void setUniformMatrix4f(const char* name, const glm::mat4 value) const;

private:
	unsigned int id;
	unsigned int compileShader(unsigned int shaderType, const char* source) const;
	void createProgram(unsigned int vsId, unsigned int fsId);
	std::string readFile(const char* fileName) const;
	unsigned int getUniformLocation(const char* name) const;

};