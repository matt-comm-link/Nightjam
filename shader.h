#pragma once
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#ifndef uint
#define uint unsigned int
#endif // !uint



class shader
{
public:
	uint ID;

	bool usable = true;

	uint projection, view, model;
	shader(const char* vertPath, const char* fragPath)
	{
		std::string vertCode;
		std::string fragCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		try
		{
			vShaderFile.open(vertPath);
			fShaderFile.open(fragPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			vShaderFile.close();
			fShaderFile.close();

			vertCode = vShaderStream.str();
			fragCode = fShaderStream.str();
		} 
		catch(std::ifstream:: failure& e)
		{
			std::cout << "Shader file fucked my dude" << std::endl;
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();

		uint vert, frag;

		vert = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert, 1, &vShaderCode, NULL);
		glCompileShader(vert);
		checkCompileErrors(vert, "VERTEX");
		
		frag = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag, 1, &fShaderCode, NULL);
		glCompileShader(frag);
		checkCompileErrors(frag, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vert);
		glAttachShader(ID, frag);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		glDeleteShader(vert);
		glDeleteShader(frag);

		projection = glGetUniformLocation(ID, "projection");
		view = glGetUniformLocation(ID, "view");
		model = glGetUniformLocation(ID, "model");

	}

	shader()
	{
		ID = -1;
		usable = false;
	}


	void use()
	{
		glUseProgram(ID);
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