#pragma once
#include <GLFW/glfw3.h>
#include "Transform.h"

// Base class
class Object {
public:
    virtual void OnCollisionEnter(Object& other) = 0;
    virtual void Render(int windowWidth, int windowHeight, float floorHeight) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual ~Object() = default;
};

// Derived classes
class Player : public Object {
public:
    Player() : x(100), y(100), width(50), height(50), velocity(0), gravity(980), jumpForce(500), isJumping(false), rotation(0), jumpIntensity(1.0f), isKeyPressed(false), keyPressDuration(0.0f) {}

    void OnCollisionEnter(Object& other) override {
        // 충돌 시 처리 코드
    }

    void Render(int windowWidth, int windowHeight, float floorHeight) override {
        float left = x - width / 2;
        float right = x + width / 2;
        float bottom = y;
        float top = y + height;

        // 테두리 그리기
        glLineWidth(3.0f);
        glColor3f(1.0f, 1.0f, 1.0f); // 흰색 테두리
        glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
        glEnd();

        // 빨간색으로 채워진 정사각형 그리기
        glPushMatrix();
        glTranslatef(x, y + height / 2, 0.0f);
        glRotatef(rotation, 0.0f, 0.0f, 1.0f);
        glTranslatef(-x, -(y + height / 2), 0.0f);
        glColor3f(1.0f, 0.0f, 0.0f); // R:255, G:0, B:0
        glBegin(GL_QUADS);
        glVertex2f(left + 3, bottom + 3);
        glVertex2f(right - 3, bottom + 3);
        glVertex2f(right - 3, top - 3);
        glVertex2f(left + 3, top - 3);
        glEnd();
        glPopMatrix();
    }

    void Update(float deltaTime) override {
        if (isJumping) {
            y += velocity * deltaTime;
            velocity -= gravity * deltaTime; // 중력 가속도 적용
            rotation += 360 * deltaTime; // 시계 방향으로 회전
            if (y <= 100.0f) { // 바닥에 닿으면
                y = 100.0f;
                isJumping = false;
                velocity = 0;
                rotation = 0;
            }
        }

        if (isKeyPressed) {
            keyPressDuration += deltaTime; // 키를 누르고 있는 동안 지속 시간 증가
            if (keyPressDuration > 1.5f) {
                keyPressDuration = 1.5f; // 최대 지속 시간 제한
            }
        }
    }

    void StartJump() {
        if (!isJumping) {
            isKeyPressed = true;
            keyPressDuration = 0.0f; // 키 누름 지속 시간 초기화
        }
    }

    void EndJump() {
        if (!isJumping && isKeyPressed) {
            isJumping = true;
            jumpIntensity = 1.0f + keyPressDuration; // 점프 강도 설정
            velocity = jumpForce * jumpIntensity; // 점프력 설정
            isKeyPressed = false;
        }
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

private:
    float x, y, width, height, velocity, gravity, jumpForce, rotation, jumpIntensity, keyPressDuration;
    bool isJumping, isKeyPressed;
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float x, float y, float width, float height, float speed)
        : x(x), y(y), width(width), height(height), speed(speed) {}

    void OnCollisionEnter(Object& other) override {
        // 충돌 시 처리 코드
    }

    void Render(int windowWidth, int windowHeight, float floorHeight) override {
        glColor3f(0.0f, 1.0f, 0.0f); // 녹색 (RGB: 0, 255, 0)
        glBegin(GL_QUADS);
        glVertex2f(x, floorHeight);
        glVertex2f(x + width, floorHeight);
        glVertex2f(x + width, floorHeight + height);
        glVertex2f(x, floorHeight + height);
        glEnd();
    }

    void Update(float deltaTime) override {
        x -= speed * deltaTime; // cm 단위로 변경하여 이동 거리 증가
        if (x + width < 0) {
            x = 800 + rand() % 800; // 화면 오른쪽으로 이동
        }
    }

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }

private:
    float x, y, width, height, speed;
};


class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // 충돌 시 처리 코드
    }
    void Render(int windowWidth, int windowHeight, float floorHeight) override {
        glColor3f(1.0f, 0.78f, 0.058f); // 황색 (RGB: 255, 200, 15)
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(windowWidth, 0);
        glVertex2f(windowWidth, floorHeight);
        glVertex2f(0, floorHeight);
        glEnd();
    }

    void Update(float deltaTime) override {
        // 바닥 업데이트 로직
    }

    float getHeight() const {
        return 100.0f; // 바닥 높이 (단위: cm)
    }
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // 충돌 시 처리 코드
    }

    void Render(int windowWidth, int windowHeight, float floorHeight) override {
        // 스타 렌더링 코드
    }

    void Update(float deltaTime) override {
        // 스타 업데이트 로직
    }
};

bool PhysicsAABB(Object& A, Object& B)
{
    Player* player = dynamic_cast<Player*>(&A);
    EnemyBlock* enemy = dynamic_cast<EnemyBlock*>(&B);
    if (player && enemy) {
        float playerLeft = player->getX() - player->getWidth() / 2;
        float playerRight = player->getX() + player->getWidth() / 2;
        float playerBottom = player->getY();
        float playerTop = player->getY() + player->getHeight();

        float enemyLeft = enemy->getX();
        float enemyRight = enemy->getX() + enemy->getWidth();
        float enemyBottom = enemy->getY();
        float enemyTop = enemy->getY() + enemy->getHeight();

        if (playerRight > enemyLeft && playerLeft < enemyRight && playerTop > enemyBottom && playerBottom < enemyTop) {
            return true; // 충돌 발생
        }
    }
    return false;
}
