#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>// include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID; //programma id
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		//hier gaan de codes in gestored worden
		std::string vertexCode; 
		std::string fragmentCode;

		//maak objects van input file stream
		std::ifstream vertexShaderFile; 
		std::ifstream fragmentShaderFile; 

		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			//open files
			vertexShaderFile.open(vertexPath); 
			fragmentShaderFile.open(fragmentPath);

			//file buffer in streams
			std::stringstream vertexShaderStream, fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();

			// doe files dicht
			vertexShaderFile.close();
			fragmentShaderFile.close();

			//maak van stream een string
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();

		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;

		}

		// maak een c string van normale string. 
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment; //ids voor individuele shaders.

		// doe source in shader en compile shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL); 
		glCompileShader(vertex); 
		checkCompileErrors(vertex, "VERTEX");

		//hetzelfde voor fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER); 
		glShaderSource(fragment, 1, &fShaderCode, NULL); 
		glCompileShader(fragment); 
		checkCompileErrors(fragment, "FRAGMENT");

		//maak je program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment); 
		glLinkProgram(ID); 
		checkCompileErrors(ID, "PROGRAM");

		// delete the vertex en fragment shader, die zijn gelinkt en we hebben ze niet meer nodig
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void use()
	{
		glUseProgram(ID); 
	}
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
private:
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};








#endif