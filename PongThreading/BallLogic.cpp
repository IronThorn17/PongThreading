#include "BallLogic.h"
#include <cmath>

BallLogic::BallLogic(float startX, float startY, float size, float speed)
    : x(startX), y(startY), size(size), speed(speed), directionX(1.0f), directionY(1.0f), canMove(false) {}

void BallLogic::startMoving() {
    canMove = true;
    directionX = -0.5f;
    directionY = 1.0f;

    float length = std::sqrt(directionX * directionX + directionY * directionY);
    if (length != 0.0f) {
        directionX /= length;
        directionY /= length;
    }
}

void BallLogic::moveBall(float deltaTime) {
    if (!canMove) return;
    std::pair<float, float> nextPos = computeNextPosition(deltaTime);
    x = nextPos.first;
    y = nextPos.second;
}

std::pair<float, float> BallLogic::computeNextPosition(float deltaTime) const {
    return { x + directionX * speed * deltaTime, y + directionY * speed * deltaTime };
}

bool BallLogic::checkTopCollision(float y, float radius) {
    return y + radius >= 1.0f;
}
bool BallLogic::checkBottomCollision(float y, float radius) {
    return y - radius <= -1.0f;
}
bool BallLogic::checkLeftScore(float x, float radius) {
    return x - radius <= -1.0f;
}
bool BallLogic::checkRightScore(float x, float radius) {
    return x + radius >= 1.0f;
}

std::vector<std::pair<float, float>> BallLogic::calculateVertices(int segments, float aspectRatio) const {
    std::vector<std::pair<float, float>> vertices;
    vertices.emplace_back(x, y); // center

    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) / segments * 2.0f * 3.14159f;
        float dx = size * std::cos(angle);
        float dy = size * std::sin(angle) * aspectRatio;
        vertices.emplace_back(x + dx, y + dy);
    }

    return vertices;
}

// Setters
void BallLogic::setPosition(float newX, float newY) { x = newX; y = newY; }
void BallLogic::setDirection(float dx, float dy) { directionX = dx; directionY = dy; }
void BallLogic::setCanMove(bool moving) { canMove = moving; }

// Getters
float BallLogic::getX() const { return x; }
float BallLogic::getY() const { return y; }
float BallLogic::getDirectionX() const { return directionX; }
float BallLogic::getDirectionY() const { return directionY; }
float BallLogic::getSize() const { return size; }
bool BallLogic::isMoving() const { return canMove; }

//Setters
void BallLogic::setSpeed(float newSpeed) {speed = newSpeed;}