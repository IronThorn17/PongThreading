#include "PaddleLogic.h"

PaddleLogic::PaddleLogic(float startX, float startY, float width, float height, float speed)
    : x(startX), y(startY), width(width), height(height), speed(speed) {}

bool PaddleLogic::tryMoveUp() {
    if (canMoveUp(y, height, speed)) {
        y += speed;
        return true;
    }
    return false;
}

bool PaddleLogic::tryMoveDown() {
    if (canMoveDown(y, height, speed)) {
        y -= speed;
        return true;
    }
    return false;
}

bool PaddleLogic::canMoveUp(float y, float height, float speed) {
    return (y + (height / 2) + speed) <= 1.0f;
}

bool PaddleLogic::canMoveDown(float y, float height, float speed) {
    return (y - (height / 2) - speed) >= -1.0f;
}

float PaddleLogic::moveUpIfPossible(float y, float height, float speed) {
    return canMoveUp(y, height, speed) ? y + speed : y;
}

float PaddleLogic::moveDownIfPossible(float y, float height, float speed) {
    return canMoveDown(y, height, speed) ? y - speed : y;
}
