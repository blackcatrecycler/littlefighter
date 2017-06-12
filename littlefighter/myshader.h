#ifndef SHADER_H_
#define SHADER_H_

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL\glew.h>

class MyShader {
public:
	GLuint Program;//着色器的构造函数
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);//构造函数 vertexPath:顶点着色器路径 fragmentPath: 片段着色器路径
	void Use();//使用函数
};

MyShader::MyShader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexCode, fragmentCode;//存储两种着色器代码
	std::ifstream vertexShaderFile, fragmentShaderFile;//文件头
	//设置抛出异常的部分
	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);
	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		//创建缓冲流
		std::stringstream vertexShaderStream, fragmentShaderStream;
		//读取文件入流
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		//关文件
		vertexShaderFile.close();
		fragmentShaderFile.close();
		//流转换为数组
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
		
	}
	catch (std::ifstream::failure e) {//抛出异常并处理
		std::cout << "ERROOR::SHADER文件不能读取" << std::endl;
	}
	//数组转化为GLchar数组
	const GLchar * vertexShaderCode = vertexCode.c_str();
	const GLchar * fragmentShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//顶点着色器定义
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	//处理错误信息
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:VERTEX编译失败\n" << infoLog << std::endl;
	}
	//片段着色器定义
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	//处理错误信息
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:FRAGMENT编译失败\n" << infoLog << std::endl;
	}
	//链接编译器
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	//处理错误信息
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:PROGRAM链接失败\n" << infoLog << std::endl;
	}
	//删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void MyShader::Use() {
	glUseProgram(this->Program);
}

#endif // !SHADER_H_
#pragma once
