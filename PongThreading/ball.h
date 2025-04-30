#ifndef BALL_H
#define BALL_H
#pragma once

#include "paddle.h"
#include <vector>
#include <utility>

class Game;

class Ball {
public:
    Ball(float startX, float startY, float size, float speed, Paddle& leftPaddle, Paddle& rightPaddle);

    void update();
    void startMoving();
    void moveBall();
    void draw() const;

    void handleScreenCollisions();
    void handlePaddleCollisions();

    // State-based accessors for testing
    float getX() const { return x; }
    float getY() const { return y; }
    float getDirectionX() const { return directionX; }
    float getDirectionY() const { return directionY; }
    bool isMoving() const { return canMove; }

    // Testable geometry
    std::vector<std::pair<float, float>> calculateVertices(int segments = 64) const;

    // State-independent testing logic
    static bool checkTopCollision(float y, float radius);
    static bool checkBottomCollision(float y, float radius);
    static bool checkLeftScore(float x, float radius);
    static bool checkRightScore(float x, float radius);
    static std::pair<float, float> computeNextPosition(float x, float y, float dx, float dy, float speed, float deltaTime);

private:
    void handleSinglePaddleCollision(const Paddle& paddle, int directionModifier);

    float x, y;
    float size;
    float speed;
    float directionX, directionY;
    bool canMove = false;

    const Paddle& leftPaddle;
    const Paddle& rightPaddle;
};
#endif