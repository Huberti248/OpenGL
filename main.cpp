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
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
	glfwInit();
	glewInit();
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL", 0, 0);
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-1, 0);
		glVertex2f(1, 0);
		glVertex2f(0, 1);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}