#include "Ball.h"
#include "game.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

Ball::Ball(float startX, float startY, float size, float speed, Paddle& leftPaddle, Paddle& rightPaddle)
    : x(startX), y(startY), size(size), speed(speed), directionX(1.0f), directionY(1.0f),
      leftPaddle(leftPaddle), rightPaddle(rightPaddle) {}

void Ball::update() {
    Ball::moveBall();
    Ball::handleScreenCollisions();
    Ball::handlePaddleCollisions();
}

void Ball::draw() {
    const int numSegments = 64;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i <= numSegments; ++i) {
        float angle = static_cast<float>(i) / static_cast<float>(numSegments) * 2.0f * 3.14159f;
        float dx = size * std::cos(angle);
        float dy = size * std::sin(angle) * (Game::getScreenWidth() / static_cast<float>(Game::getScreenHeight()));
        glVertex2f(x + dx, y + dy);
    }

    glEnd();
}

void Ball::startMoving() {
    canMove = true;

    // Generate random direction components between -1 and 1
    directionX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
    directionY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;

    directionX = -0.5f;
    directionY = 1.0f;

    // Normalize the vector to ensure consistent speed
    float length = std::sqrt(directionX * directionX + directionY * directionY);
    if (length != 0.0f) {
        directionX /= length;
        directionY /= length;
    }
}

void Ball::moveBall() {
    if (canMove) {
        x += directionX * speed * 0.016f;
        y += directionY * speed * 0.016f;
    }
}

void Ball::handleScreenCollisions() {
    // Check for collision with the top/bottom of the screen
    if (y + size >= 1) {
        // Reverse the direction (simulate bounce)
        directionY = -std::abs(directionY);
    }
    else if (y - size <= -1) {
        directionY = std::abs(directionY);
    }

    // Check for collisions with the sides of the screen
    if (x + size >= 1) {
        // Add Point to Player 1
        std::cout << "Right Screen" << std::endl;
    }
    else if (x - size <= -1) {
        // Add Point to Player 2
        std::cout << "Left Screen" << std::endl;
    }
}

void Ball::handlePaddleCollisions() {
    handleSinglePaddleCollision(leftPaddle, -1);
    handleSinglePaddleCollision(rightPaddle, 1);
}

void Ball::handleSinglePaddleCollision(const Paddle& paddle, int directionModifier) {
    float ballRadius = size;
    float paddleTop = paddle.y + (paddle.height / 2);
    float paddleBottom = paddle.y - (paddle.height / 2);
    float paddleEdge = paddle.x + -directionModifier * paddle.width / 2;

    // Check if the ball is within the horizontal and vertical bounds of the paddle
    if (x + ballRadius >= paddleEdge && x - ballRadius <= paddleEdge &&
        y + ballRadius >= paddleBottom && y - ballRadius <= paddleTop) {

        // Calculate the portion of the paddle hit by the ball
        float portionHit = (y - paddle.y) / (paddle.height / 2);

        // Check if the ball is hitting within the specified horizontal region
        if (std::abs(x - paddleEdge) <= 0.05f) {
            // Adjust the ball's direction based on the portion hit
            if (portionHit > 0.66) {
                // Hit the top portion of the paddle, add more upward motion
                directionY += 0.2f;
            }
            else if (portionHit < -0.66) {
                // Hit the bottom portion of the paddle, add more downward motion
                directionY -= 0.2f;
            }
            else {
                // Hit the middle portion, maintain normal rebound
                // You can add additional logic or adjust directionX if needed
            }

            // Reverse the directionX to simulate bounce
            directionX = -directionX;
        }
    }
}