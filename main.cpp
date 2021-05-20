#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <filesystem>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

unsigned compileShader(const std::string& source, int type)
{
	unsigned shaderId = glCreateShader(type);
	const char* buffer = source.c_str();
	glShaderSource(shaderId, 1, &buffer, 0);
	glCompileShader(shaderId);
	int compiled;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_TRUE) {
		std::cout << source << std::endl;
		return shaderId;
	}
	else {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetShaderInfoLog(shaderId, length, 0, &message[0]);
		std::cout << "Cannot compile shader" << std::endl << source << std::endl << std::string(message.begin(), message.end()) << std::endl;
		glDeleteShader(shaderId);
		return 0;
	}
}

// NOTE: Remember to call glDeleteProgram()
unsigned createProgram(unsigned vertexShaderId, unsigned fragmentShaderId)
{
	unsigned programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	int linked;
	glGetProgramiv(programId, GL_LINK_STATUS, &linked);
	// NOTE: No need to call glDetachShader(), because future calls to glDeleteProgram() will do that automatically
	if (linked == GL_TRUE) {
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		return programId;
	}
	else {
		int length;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> message(length);
		glGetProgramInfoLog(programId, length, 0, &message[0]);
		std::cout << "Cannot link program" << std::endl << std::string(message.begin(), message.end()) << std::endl;
		glDeleteProgram(programId);
		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		return 0;
	}
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

int main()
{
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "OpenGL", 0, 0);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetKeyCallback(window, keyCallback);

	float positions[]{
		-0.5f, -0.5f,
		-0.0f,  0.5f,
		 0.5f, -0.5f,
	};

	unsigned vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	std::string vertexShader = R"(
#version 330 core

layout (location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}
)";
	std::string fragmentShader = R"(
#version 330 core

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(0.0, 1.0, 0.0, 1.0);
}
)";

	unsigned vs = compileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
	unsigned programId = createProgram(vs, fs);
	glUseProgram(programId);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	bool showDemoWindow = true;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (showDemoWindow) {
			ImGui::ShowDemoWindow(&showDemoWindow);
		}
		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}
}