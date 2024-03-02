#include "paddle.h"
#include <GLFW/glfw3.h>
#include <iostream>

Paddle::Paddle(float startX, float startY, float width, float height, float speed)
    : x(startX), y(startY), width(width), height(height), speed(speed) {}

void Paddle::moveUp() {
    if ((y + (height / 2)) <= 1)
        y += speed;
}

void Paddle::moveDown() {
    if ((y - (height / 2)) >= -1)
        y -= speed;
}

void Paddle::update() {
    // Add any additional logic for paddle update
}

void Paddle::draw() {
    glBegin(GL_QUADS);
    glVertex2f(x - (width / 2), y - (height / 2));
    glVertex2f(x - (width / 2), y + (height / 2));
    glVertex2f(x + (width / 2), y + (height / 2));
    glVertex2f(x + (width / 2), y - (height / 2));
    glEnd();
}
