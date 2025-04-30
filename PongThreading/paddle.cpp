#include "paddle.h"
#include <GLFW/glfw3.h>

void Paddle::draw() const {
    glBegin(GL_QUADS);
    glVertex2f(getX() - (getWidth() / 2), getY() - (getHeight() / 2));
    glVertex2f(getX() - (getWidth() / 2), getY() + (getHeight() / 2));
    glVertex2f(getX() + (getWidth() / 2), getY() + (getHeight() / 2));
    glVertex2f(getX() + (getWidth() / 2), getY() - (getHeight() / 2));
    glEnd();
}

