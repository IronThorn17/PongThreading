#include "paddle.h"
#include <GLFW/glfw3.h>

Paddle::Paddle(float startX, float startY, float width, float height, float speed)
    : x(startX), y(startY), width(width), height(height), speed(speed) {}

bool Paddle::tryMoveUp() {
    if (canMoveUp(y, height, speed)) {
        y += speed;
        return true;
    }
    return false;
}

bool Paddle::tryMoveDown() {
    if (canMoveDown(y, height, speed)) {
        y -= speed;
        return true;
    }
    return false;
}

void Paddle::draw() const {
    glBegin(GL_QUADS);
    glVertex2f(x - (width / 2), y - (height / 2));
    glVertex2f(x - (width / 2), y + (height / 2));
    glVertex2f(x + (width / 2), y + (height / 2));
    glVertex2f(x + (width / 2), y - (height / 2));
    glEnd();
}

// Static testable logic
bool Paddle::canMoveUp(float y, float height, float speed) {
    return (y + (height / 2)) <= 1.0f;
}

bool Paddle::canMoveDown(float y, float height, float speed) {
    return (y - (height / 2)) >= -1.0f;
}

float Paddle::moveUpIfPossible(float y, float height, float speed) {
    return canMoveUp(y, height, speed) ? y + speed : y;
}

float Paddle::moveDownIfPossible(float y, float height, float speed) {
    return canMoveDown(y, height, speed) ? y - speed : y;
}
