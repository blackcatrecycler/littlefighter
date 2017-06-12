#ifndef SHADER_H_
#define SHADER_H_

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

#include<GL\glew.h>

class MyShader {
public:
	GLuint Program;//��ɫ���Ĺ��캯��
	MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);//���캯�� vertexPath:������ɫ��·�� fragmentPath: Ƭ����ɫ��·��
	void Use();//ʹ�ú���
};

MyShader::MyShader(const GLchar* vertexPath, const GLchar* fragmentPath) {
	std::string vertexCode, fragmentCode;//�洢������ɫ������
	std::ifstream vertexShaderFile, fragmentShaderFile;//�ļ�ͷ
	//�����׳��쳣�Ĳ���
	vertexShaderFile.exceptions(std::ifstream::badbit);
	fragmentShaderFile.exceptions(std::ifstream::badbit);
	try {
		vertexShaderFile.open(vertexPath);
		fragmentShaderFile.open(fragmentPath);
		//����������
		std::stringstream vertexShaderStream, fragmentShaderStream;
		//��ȡ�ļ�����
		vertexShaderStream << vertexShaderFile.rdbuf();
		fragmentShaderStream << fragmentShaderFile.rdbuf();
		//���ļ�
		vertexShaderFile.close();
		fragmentShaderFile.close();
		//��ת��Ϊ����
		vertexCode = vertexShaderStream.str();
		fragmentCode = fragmentShaderStream.str();
		
	}
	catch (std::ifstream::failure e) {//�׳��쳣������
		std::cout << "ERROOR::SHADER�ļ����ܶ�ȡ" << std::endl;
	}
	//����ת��ΪGLchar����
	const GLchar * vertexShaderCode = vertexCode.c_str();
	const GLchar * fragmentShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	//������ɫ������
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	//���������Ϣ
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:VERTEX����ʧ��\n" << infoLog << std::endl;
	}
	//Ƭ����ɫ������
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	//���������Ϣ
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:FRAGMENT����ʧ��\n" << infoLog << std::endl;
	}
	//���ӱ�����
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertex);
	glAttachShader(this->Program, fragment);
	glLinkProgram(this->Program);
	//���������Ϣ
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER:PROGRAM����ʧ��\n" << infoLog << std::endl;
	}
	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void MyShader::Use() {
	glUseProgram(this->Program);
}

#endif // !SHADER_H_
#pragma once
