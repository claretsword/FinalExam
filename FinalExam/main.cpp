﻿#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include "Object.h"

void errorCallback(int error, const char* description)
{
	printf("GLFW Error: %s", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}

int Physics()
{
	return 0;
}

int Initialize()
{
	return 0;
}

int Update()
{
	return 0;
}

int Render(Player& player)
{
	// 배경색 설정 (하늘색: R:0, G:30, B:100)
	glClearColor(0.0f, 0.12f, 0.39f, 1.0f); // R: 0/255, G: 30/255, B: 100/255
	glClear(GL_COLOR_BUFFER_BIT);

	//플레이어 렌더링
	player.Render();
	
	
	return 0;

	
}


int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//glfw라이브러리 초기화
	if (!glfwInit())
		return -1;

	GLFWwindow* window;
	window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetErrorCallback(errorCallback);
	glfwSetKeyCallback(window, keyCallback);

	Initialize();
	
	// Player 객체 생성
	Player player;
	
	
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		Physics();
		Update();
		Render(player);
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;

}