#pragma once

#include "paddle.h"

class Ball {
public:
    float x, y; // Ball's position
    float dx, dy; // Ball's movement delta
    float radius; // Ball's radius
    bool canMove; // Flag to control the movement

    Ball(); // Constructor does not take Paddle references anymore
    void startMovement();
    void update(const Paddle& leftPaddle, const Paddle& rightPaddle); // Update method now takes paddles as arguments
    void draw() const;
    void resetPosition();

private:
    void handlePaddleCollision(const Paddle& leftPaddle, const Paddle& rightPaddle);
};



