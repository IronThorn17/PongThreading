#pragma once

#include "paddle.h"

class Ball {
public:
    Ball(float startX, float startY, float size, float speed, Paddle& leftPaddle, Paddle& rightPaddle);
    void update();
    void draw();
    void startMoving();
    void moveBall();
    void handleScreenCollisions();
    void handlePaddleCollisions();
    void handleSinglePaddleCollision(const Paddle& paddle, int directionModifier);

private:
    float x, y, size, speed;
    float directionX, directionY;
    bool canMove;
    Paddle& leftPaddle;
    Paddle& rightPaddle;
};
