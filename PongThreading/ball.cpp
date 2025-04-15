#include "ball.h"
#include "game.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>

Ball::Ball(float startX, float startY, float size, float speed, Paddle& leftPaddle, Paddle& rightPaddle)
    : x(startX), y(startY), size(size), speed(speed), directionX(1.0f), directionY(1.0f),
    leftPaddle(leftPaddle), rightPaddle(rightPaddle) {}

void Ball::update() {
    moveBall();
    handleScreenCollisions();
    handlePaddleCollisions();
}

void Ball::startMoving() {
    canMove = true;

    directionX = -0.5f;
    directionY = 1.0f;

    float length = std::sqrt(directionX * directionX + directionY * directionY);
    if (length != 0.0f) {
        directionX /= length;
        directionY /= length;
    }
}

void Ball::moveBall() {
    if (canMove) {
        std::pair<float, float> nextPos = computeNextPosition(x, y, directionX, directionY, speed, 0.016f);
        x = nextPos.first;
        y = nextPos.second;
    }
}

void Ball::draw() const {
    const auto vertices = calculateVertices();
    glBegin(GL_TRIANGLE_FAN);
    for (const auto& vertex : vertices)
        glVertex2f(vertex.first, vertex.second);
    glEnd();
}

std::vector<std::pair<float, float>> Ball::calculateVertices(int segments) const {
    std::vector<std::pair<float, float>> vertices;
    vertices.emplace_back(x, y); // center

    float aspectRatio = Game::getScreenWidth() / static_cast<float>(Game::getScreenHeight());

    for (int i = 0; i <= segments; ++i) {
        float angle = static_cast<float>(i) / segments * 2.0f * 3.14159f;
        float dx = size * std::cos(angle);
        float dy = size * std::sin(angle) * aspectRatio;
        vertices.emplace_back(x + dx, y + dy);
    }

    return vertices;
}

void Ball::handleScreenCollisions() {
    if (checkTopCollision(y, size)) directionY = -std::abs(directionY);
    else if (checkBottomCollision(y, size)) directionY = std::abs(directionY);

    if (checkRightScore(x, size)) {
        // Player 1 scores
    }
    else if (checkLeftScore(x, size)) {
        // Player 2 scores
    }
}

bool Ball::checkTopCollision(float y, float radius) {
    return y + radius >= 1.0f;
}

bool Ball::checkBottomCollision(float y, float radius) {
    return y - radius <= -1.0f;
}

bool Ball::checkRightScore(float x, float radius) {
    return x + radius >= 1.0f;
}

bool Ball::checkLeftScore(float x, float radius) {
    return x - radius <= -1.0f;
}

std::pair<float, float> Ball::computeNextPosition(float x, float y, float dx, float dy, float speed, float deltaTime) {
    return {
        x + dx * speed * deltaTime,
        y + dy * speed * deltaTime
    };
}

void Ball::handlePaddleCollisions() {
    handleSinglePaddleCollision(leftPaddle, -1);
    handleSinglePaddleCollision(rightPaddle, 1);
}

void Ball::handleSinglePaddleCollision(const Paddle& paddle, int directionModifier) {
    float ballRadius = size;
    float paddleTop = paddle.getY() + (paddle.getHeight() / 2);
    float paddleBottom = paddle.getY() - (paddle.getHeight() / 2);
    float paddleEdge = paddle.getX() + -directionModifier * paddle.getWidth() / 2;

    if (x + ballRadius >= paddleEdge && x - ballRadius <= paddleEdge &&
        y + ballRadius >= paddleBottom && y - ballRadius <= paddleTop) {

        float portionHit = (y - paddle.getY()) / (paddle.getHeight() / 2);

        if (std::abs(x - paddleEdge) <= 0.05f) {
            if (portionHit > 0.66f) directionY += 0.2f;
            else if (portionHit < -0.66f) directionY -= 0.2f;

            directionX = -directionX;
        }
    }
}
