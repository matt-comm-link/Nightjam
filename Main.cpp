#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <glm.hpp>



#include <filesystem>
#include <string>

#include "mesh.h"

#include "Loader.h"

#ifndef uint
#define uint unsigned int
#endif // !uint

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);






int main(int argc, char* argv[])
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << argv[0] << std::endl;

	std::string  AppPath = { std::filesystem::current_path().string() };
	AppPath.erase(remove(AppPath.begin(), AppPath.end(), '\"'), AppPath.end());
	AppPath += "\\resources\\";
	std::cout << AppPath << std::endl;
	//ApplicationPath = AppPath;

	Wwidth = 640;
	Wheight = 480;


	GLFWwindow* window = glfwCreateWindow(Wwidth, Wheight, "NightJam", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, Wwidth, Wheight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glCullFace(GL_BACK);



	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	//GAME INITIALISATION
	SetupGame(AppPath);
	
	double lastTime = 0;

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		//input
		processInput(window);

		//Game logic

		globalView = glm::lookAt(campos, campos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		//render
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw Scene 
		DrawMesh(CurrentScene.limits);
		//CurrentScene.limits.modelRot += deltaTime;
		//std::cout << CurrentScene.limits.modelRot << std::endl;
		//for (uint i = 0; i < CurrentScene.Objects.size(); i++)
		//{
		//	DrawBounds(CurrentScene.Objects[i]);
		//}
		//Draw Battle
		//Draw Conversation
		DrawText("'The quick brown fox jumped over the lazy dog' - confucious.", "courbd", glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec4(1, 1, 1, 1));

		//Choose to draw characters based on the above

		//buffer swap
		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	glfwTerminate();
	return 0;

	
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput (GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}