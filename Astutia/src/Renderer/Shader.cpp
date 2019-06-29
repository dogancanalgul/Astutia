#include "Shader.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>

Shader::Shader() 
	: id(0) {
	//Take in the shaders from shader directory.
	std::string vertexShader = readFile("res/shader/vs.shader");

	std::string fragmentShader = readFile("res/shader/fs.shader");

	//send shaders to opengl and compile them
	unsigned int vertexId = compileShader(GL_VERTEX_SHADER, vertexShader.c_str());
	unsigned int fragmentId = compileShader(GL_FRAGMENT_SHADER, fragmentShader.c_str());

	//create a program and link the shaders
	createProgram(vertexId, fragmentId);

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);
}

std::string Shader::readFile(const char* fileName) const{
	std::fstream fRead(fileName);
	return std::string((std::istreambuf_iterator<char>(fRead)),
		std::istreambuf_iterator<char>());

}

unsigned int Shader::compileShader(unsigned int shaderType, const char* source) const {
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &source, NULL);
	glCompileShader(shaderId);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << (GL_VERTEX_SHADER == shaderType ? "VERTEX" : "FRAGMENT" ) <<  "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shaderId;
}

void Shader::createProgram(unsigned int vsId, unsigned int fsId) {
	this->id = glCreateProgram();
	glAttachShader(this->id, vsId);
	glAttachShader(this->id, fsId);
	glLinkProgram(this->id);
	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

Shader::~Shader() {
	glDeleteProgram(this->id);
}

void Shader::bind() const {
	glUseProgram(this->id);
}
void Shader::unbind() const{
	glUseProgram(0);
}
	
void Shader::setUniform1i(const char* name, const int value) const{
	glUniform1i(getUniformLocation(name), value);
}
void Shader::setUniform1f(const char* name, const float value) const {
	glUniform1f(getUniformLocation(name), value);
}
void Shader::setUniform3f(const char* name, const float v1, const float v2, const float v3) const {
	glUniform3f(getUniformLocation(name), v1, v2, v3);
}
void Shader::setUniform3fv(const char* name, const glm::vec3 value) const {
	glUniform3fv(getUniformLocation(name), 1, &value.x);
}
void Shader::setUniformMatrix4f(const char* name, const glm::mat4 value) const {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
unsigned int Shader::getUniformLocation(const char* name) const{
	return glGetUniformLocation(this->id, name);
}

