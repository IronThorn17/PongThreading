#include "paddle.h"
#include <GLFW/glfw3.h>

Paddle::Paddle(float posX, float posY) : x(posX), y(posY), speed(0.0005f), up(false), down(false) {}

void Paddle::update() {
    if (up && y < 1 - 0.15f) y += speed; // The paddle's top edge is below the top boundary
    if (down && y > -1 + 0.15f) y -= speed; // The paddle's bottom edge is above the bottom boundary
}

void Paddle::draw() const {
    glBegin(GL_QUADS);
    glVertex2f(x - 0.02f, y - 0.15f);
    glVertex2f(x + 0.02f, y - 0.15f);
    glVertex2f(x + 0.02f, y + 0.15f);
    glVertex2f(x - 0.02f, y + 0.15f);
    glEnd();
}
