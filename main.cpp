#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include "data.h"

GLFWwindow* window;
unsigned int VBO;
unsigned int VAO;
unsigned int shaderProgram;
unsigned int EBO;

void windowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool initializeWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "OpenGL Sandbox", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, windowResized);
	return true;
}

void logErrors(bool success, unsigned int object, const char* errorType)
{
	char infoLog[512];
	if (!success) {
		glGetProgramInfoLog(object, 512, NULL, infoLog);
		std::cout << errorType << " FAILED\n" << infoLog << std::endl;
	}
}

int createShader(const char* source, unsigned int shaderType, const char* errorType) {
	unsigned int shader;
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int  success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	logErrors(success, shader, errorType);
	return shader;
}

void createProgram() {
	unsigned int vertexShader = createShader(vertexShaderSource, GL_VERTEX_SHADER, "ERROR::SHADER::VERTEX::COMPILATION");
	unsigned int fragmentShader = createShader(fragmentShaderSource, GL_FRAGMENT_SHADER, "ERROR::SHADER::FRAGMENT::COMPILATION");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int  success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	logErrors(success, shaderProgram, "ERROR::SHADER::PROGRAM::COMPILATION" );

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void createVertexArray() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	if (!initializeWindow())
		return -1;

	createVertexArray();
	createProgram();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

