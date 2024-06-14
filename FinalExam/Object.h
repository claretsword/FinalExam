#pragma once
// Base class
#include <GLFW/glfw3.h>
class Object {
public:
    virtual void OnCollisionEnter(Object& other) = 0;
        virtual void Render() = 0; 
    
};

// Derived classes
class Player : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }

    void Render() override {
        
        float size_cm = 50.0f/100.0f; // 정사각형 한 변의 길이 (단위: cm)
        float bordersize_cm = 3.0f/100.0f; // 테두리 두께 (단위: cm)

        // 1cm = 1px로 가정
        float size_px = size_cm * 1.0f; // 정사각형 한 변의 길이 (단위: px)
        float bordersize_px = bordersize_cm * 1.0f; // 테두리 두께 (단위: px)

        // 정사각형 좌표 계산
        float left = -size_px / 2;
        float right = size_px / 2;
        float bottom = -size_px / 2;
        float top = size_px / 2;

        // 테두리 그리기
        glLineWidth(bordersize_px);
        glColor3f(1.0f, 1.0f, 1.0f); // 흰색 테두리
        glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
        glEnd();

        // 빨간색으로 채워진 정사각형 그리기
        glColor3f(1.0f, 0.0f, 0.0f); // R:255, G:0, B:0
        glBegin(GL_QUADS);
        glVertex2f(left + bordersize_px, bottom + bordersize_px);
        glVertex2f(right - bordersize_px, bottom + bordersize_px);
        glVertex2f(right - bordersize_px, top - bordersize_px);
        glVertex2f(left + bordersize_px, top - bordersize_px);
        glEnd();
    }
        
    

};

class EnemyBlock : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
    void Render() override {
        float floorHeight = 0.1f; // 바닥 높이 (1m)

        glColor3f(1.0f, 0.78f, 0.058f); // 황색 (RGB: 255, 200, 15)
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f + floorHeight);
        glVertex2f(-1.0f, -1.0f + floorHeight);
        glEnd();
        
    }

  
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
    }
};


int PhysicsAABB(Object& A, Object& B)
{
    return 0;
}