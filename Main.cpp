#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <glm.hpp>



#include <filesystem>
#include <string>

#include "mesh.h"

#include "Environment.h"
#include "framebuffering.h"


#include "Loader.h"
#include "RenderHelpers.h"

#ifndef uint
#define uint unsigned int
#endif // !uint

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//Framebuffers for rendering the game in original aspect ratio, as well as one for post processing effects if needed.




Environment environment;


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

	environment.Wwidth = environment.Twidth;
	environment.Wheight = environment.Theight;


	GLFWwindow* window = glfwCreateWindow(environment.Wwidth, environment.Wheight, "NightJam", NULL, NULL);

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

	glViewport(0, 0, environment.Wwidth, environment.Wheight);

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
	SetupGame(AppPath, environment);
	
	framebuffer_size_callback(window, environment.Wwidth, environment.Wheight);
	environment.gameBuffer = FrameBuffer(environment.RWidth, environment.RHeight, GL_NEAREST, environment.GetMeshInstance("renbuffer"));
	environment.postBuffer = FrameBuffer(environment.Wwidth, environment.Wheight, GL_NEAREST, environment.GetMeshInstance("renbuffer"));

	double lastTime = 0;
	environment.postView = glm::lookAt(glm::vec3(0, 0, 1), environment.campos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));


	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		environment.deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		//input
		processInput(window);

		//Game logic

		environment.globalView = glm::lookAt(environment.campos, environment.campos + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

		//render
		environment.gameBuffer.Use();
		glEnable(GL_DEPTH_TEST);
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw Scene 
		DrawMesh(environment, environment.CurrentScene.limits);
		environment.CurrentScene.limits.modelRot += environment.deltaTime;
		//std::cout << CurrentScene.limits.modelRot << std::endl;
		//for (uint i = 0; i < CurrentScene.Objects.size(); i++)
		//{
		//	DrawBounds(CurrentScene.Objects[i]);
		//}
		//Draw Battle
		//Choose to draw characters based on the above
		
		//Draw Conversation;
		DrawText(environment, "'The quick brown fox jumped over the lazy dog' - confucious.", "CascadiaCode", glm::vec3(0, 0, 0), glm::vec3(0.2f, 0.5f, 1), glm::vec4(1, 1, 1, 1));
		DrawText(environment, ("x = " + to_string(environment.InputMousePos.x) + ", y = " + to_string(environment.InputMousePos.y)), "CascadiaCode", glm::vec3(14, 440, 0), glm::vec3(0.3f, 0.3f, 1), glm::vec4(1, 0, 0, 1));

		DrawFB(environment, environment.gameBuffer, "BufferShader");


		//buffer swap
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwTerminate();
	return 0;

	
}




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{

	glViewport(0, 0, width, height);
	environment.Wwidth = width;
	environment.Wheight = height;

	float targetratio = environment.TwidthR / environment.TheightR;
	float currentratio = environment.Wwidth / environment.Wheight;

	float scaleWidth = environment.TwidthR / environment.Wwidth;
	float scaleHeight = environment.TheightR / environment.Wwidth;



	if(currentratio > targetratio)
	{
		environment.wRatioAdjust = currentratio / targetratio;
		environment.hRatioAdjust = 1;

		environment.RWidth = height * targetratio;
		environment.RHeight = height;
	}
	else
	{
		environment.wRatioAdjust = 1;
		environment.hRatioAdjust = (1 / currentratio) / (1 / targetratio);

		environment.RWidth = width;
		environment.RHeight = width * (1/targetratio);
	}
	//environment.gameBuffer.Resize(640, 480);
	//environment.postOrtho = glm::ortho(0.0f, environment.RWidth, 0.0f, environment.RHeight, 10.0f, -10.0f);

}

void processInput (GLFWwindow* window)
{
	environment.InputLastMouse0 = environment.InputMouse0;
	environment.InputLastMouse1 = environment.InputMouse1;
	environment.InputLastESC = environment.InputESC;
	environment.InputLastSpace = environment.InputSpace;
	
	environment.InputMouse0 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
	environment.InputMouse1 = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
	environment.InputESC = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
	environment.InputSpace == glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;

	environment.InputWASD = glm::vec2(0, 0);
	//In order of the initialisation even though it's a mess readability wise in programming
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		environment.InputWASD.y += 1;
	}	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		environment.InputWASD.x -= 1;
	}	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		environment.InputWASD.y -= 1;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		environment.InputWASD.x += 1;
	}
	glm::dvec2 mposinput;
	glfwGetCursorPos(window, &mposinput.x, &mposinput.y);
	mposinput -= environment.MPosOffset;

	environment.InputLastMousePos = environment.InputMousePos;
	environment.InputMousePos = glm::vec2(mposinput.x, environment.RHeight - mposinput.y);
	environment.InputMouseCentred = glm::vec2(environment.InputMousePos.x - (environment.Wwidth / 2), environment.InputMousePos.y - (environment.Wheight / 2));





}

