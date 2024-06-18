#pragma once
#include <GLFW/glfw3.h>

// Base class
class Object {
public:
    virtual void OnCollisionEnter(Object& other) = 0;
    virtual void Render(int windowWidth, int windowHeight) = 0;
};

// Derived classes
class Player : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // �浹 �� ó�� �ڵ�
    }

    void Render(int windowWidth, int windowHeight) override {
        float size_cm = 50.0f; // ���簢�� �� ���� ���� (����: cm)
        float border_size_cm = 3.0f; // �׵θ� �β� (����: cm)

        // â�� ũ��� ���� ũ�⸦ ������ ��ȯ�Ͽ� ���
        float left = (windowWidth - size_cm) / 2.0f;
        float right = left + size_cm;
        float bottom = (windowHeight - size_cm) / 2.0f;
        float top = bottom + size_cm;

        // �׵θ� �׸���
        glLineWidth(border_size_cm);
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
        glVertex2f(left + border_size_cm, bottom + border_size_cm);
        glVertex2f(right - border_size_cm, bottom + border_size_cm);
        glVertex2f(right - border_size_cm, top - border_size_cm);
        glVertex2f(left + border_size_cm, top - border_size_cm);
        glEnd();
    }
};

class EnemyBlock : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // �浹 �� ó�� �ڵ�
    }
    void Render(int windowWidth, int windowHeight) override {
        // ������ �ڵ�
    }
};

class Floor : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // �浹 �� ó�� �ڵ�
    }
    void Render(int windowWidth, int windowHeight) override {
        float floorHeight_cm = 100.0f; // �ٴ� ���� (����: cm)

        glColor3f(1.0f, 0.78f, 0.058f); // Ȳ�� (RGB: 255, 200, 15)
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(windowWidth, 0);
        glVertex2f(windowWidth, floorHeight_cm);
        glVertex2f(0, floorHeight_cm);
        glEnd();
    }
};

class Star : public Object {
public:
    void OnCollisionEnter(Object& other) override {
        // �浹 �� ó�� �ڵ�
    }
};

int PhysicsAABB(Object& A, Object& B)
{
    // AABB �浹 �˻�
    return 0;
}
