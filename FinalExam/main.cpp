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
#include "Transform.h"

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Player* player = static_cast<Player*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS) {
            player->StartJump(); // 점프 시작
        }
        else if (action == GLFW_RELEASE) {
            player->EndJump(); // 점프 종료 및 실행
        }
    }
}

int Physics(Player& player, EnemyBlock enemies[], int enemyCount)
{
    for (int i = 0; i < enemyCount; ++i) {
        if (PhysicsAABB(player, enemies[i])) {
            printf("Game Over\n");
            return -1; // 게임 종료
        }
    }
    return 0;
}

int Initialize()
{
    // 초기화 관련 처리를 여기에 추가할 수 있습니다.
    return 0;
}

int Update(Player& player, Floor& floor, EnemyBlock enemies[], int enemyCount, Star stars[], int starCount, float deltaTime)
{
    // 업데이트 관련 처리를 여기에 추가할 수 있습니다.
    player.Update(deltaTime);
    floor.Update(deltaTime);

    for (int i = 0; i < enemyCount; ++i) {
        enemies[i].Update(deltaTime);
    }

    for (int i = 0; i < starCount; ++i) {
        stars[i].Update(deltaTime);
    }

    return 0;
}

int Render(Player& player, Floor& floor, EnemyBlock enemies[], int enemyCount, Star stars[], int starCount, int windowWidth, int windowHeight)
{
    // 배경색 설정 (하늘색: R:0, G:30, B:100)
    glClearColor(0.0f, 0.12f, 0.39f, 1.0f); // R: 0/255, G: 30/255, B: 100/255
    glClear(GL_COLOR_BUFFER_BIT);

    // 좌표계를 픽셀 단위로 설정
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, 0, windowHeight, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // 바닥 높이 가져오기
    float floorHeight = floor.getHeight();

    // 바닥 렌더링
    floor.Render(windowWidth, windowHeight, floorHeight);

    // 플레이어 렌더링
    player.Render(windowWidth, windowHeight, floorHeight);

    // 장애물 렌더링
    for (int i = 0; i < enemyCount; ++i) {
        enemies[i].Render(windowWidth, windowHeight, floorHeight);
    }

    // 별 렌더링
    for (int i = 0; i < starCount; ++i) {
        stars[i].Render(windowWidth, windowHeight, floorHeight);
    }

    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // glfw 라이브러리 초기화
    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Player player;
    glfwSetWindowUserPointer(window, &player);

    Initialize();

    // Floor 객체 생성
    Floor floor;

    // 장애물 생성 (가로 50cm, 높이 100cm 및 300cm, 속도 150cm/s)
    const int enemyCount = 4;
    EnemyBlock enemies[enemyCount] = {
        {1200, 0, 50, 100, 150.0f}, // 낮은 장애물
        {2400, 0, 50, 100, 150.0f}, // 낮은 장애물
        {1800, 0, 50, 300, 150.0f}, // 높은 장애물
        {3600, 0, 50, 300, 150.0f}  // 높은 장애물
    };

    // 별 생성 (속도는 블록 속도의 1/3)
    const int starCount = 5;
    Star stars[starCount] = {
        {800, 500, 10, 50.0f},
        {1200, 550, 20, 50.0f},
        {1600, 600, 15, 50.0f},
        {2000, 650, 25, 50.0f},
        {2400, 700, 18, 50.0f}
    };

    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // 시간 계산
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        if (Physics(player, enemies, enemyCount) == -1) {
            break; // 게임 종료
        }

        Update(player, floor, enemies, enemyCount, stars, starCount, deltaTime.count());

        int windowWidth, windowHeight;
        glfwGetFramebufferSize(window, &windowWidth, &windowHeight);

        Render(player, floor, enemies, enemyCount, stars, starCount, windowWidth, windowHeight);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
