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
        
        float size_cm = 50.0f/100.0f; // ���簢�� �� ���� ���� (����: cm)
        float bordersize_cm = 3.0f/100.0f; // �׵θ� �β� (����: cm)

        // 1cm = 1px�� ����
        float size_px = size_cm * 1.0f; // ���簢�� �� ���� ���� (����: px)
        float bordersize_px = bordersize_cm * 1.0f; // �׵θ� �β� (����: px)

        // ���簢�� ��ǥ ���
        float left = -size_px / 2;
        float right = size_px / 2;
        float bottom = -size_px / 2;
        float top = size_px / 2;

        // �׵θ� �׸���
        glLineWidth(bordersize_px);
        glColor3f(1.0f, 1.0f, 1.0f); // ��� �׵θ�
        glBegin(GL_LINE_LOOP);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
        glVertex2f(left, top);
        glEnd();

        // ���������� ä���� ���簢�� �׸���
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
        float floorHeight = 0.1f; // �ٴ� ���� (1m)

        glColor3f(1.0f, 0.78f, 0.058f); // Ȳ�� (RGB: 255, 200, 15)
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