#pragma once

float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};
unsigned int indices[] = {
	0, 1, 2
};

const char* vertexShaderSource =
R"##(
	#version 330 core
	
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;
	out vec4 vertexColor;

	void main()
	{
		gl_Position = vec4(aPos, 1.0);
		vertexColor = vec4(aColor, 1.0);
	}
)##";

const char* fragmentShaderSource =
R"##(
	#version 330 core

	out vec4 FragColor;
	in vec4 vertexColor;

	void main()
	{
		FragColor = vertexColor;
	}
)##";