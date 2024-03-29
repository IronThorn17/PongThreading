#include "Ball.h"
#include "paddle.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib> // Include for std::rand() and std::srand()
#include <ctime>   // Include for std::time()

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Ball::Ball() : x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), radius(0.02f), canMove(false) {}

void Ball::startMovement() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Randomly choose the direction to be either left (-1) or right (1)
    int direction = (std::rand() % 2) * 2 - 1; // This will generate either -1 or 1

    dx = 0.0005f * direction; // Apply the direction to dx
    dy = 0.0f; // Ensure there's no vertical movement

    canMove = true;
}

void Ball::update(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    if (!canMove) return;

    x += dx;
    y += dy;

    // Collision with the top or bottom of the screen
    if (y + radius >= 1.0f || y - radius <= -1.0f) {
        dy = -dy;
    }

    // Reset if it goes past the left or right edge
    if (x + radius > 1.0f || x - radius < -1.0f) {
        resetPosition();
    }

    // Handle collisions with the paddles
    handlePaddleCollision(leftPaddle, rightPaddle);
}

void Ball::handlePaddleCollision(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    // This is the constant speed of the ball.
    const float constantSpeed = std::sqrt(dx * dx + dy * dy);

    // Collision with left paddle
    if (x - radius < leftPaddle.x + 0.02f && x + radius > leftPaddle.x - 0.02f &&
        y + radius > leftPaddle.y - 0.15f && y - radius < leftPaddle.y + 0.15f) {
        dx = constantSpeed; // Bounce right with constant speed

        // Adjust dy based on collision point, limit the maximum angle
        float hitPoint = (y - leftPaddle.y) / (0.15f * 2); // Normalize hit point to [-0.5, 0.5]
        dy = constantSpeed * hitPoint; // Adjust vertical direction based on hit point
    }

    // Collision with right paddle
    if (x + radius > rightPaddle.x - 0.02f && x - radius < rightPaddle.x + 0.02f &&
        y + radius > rightPaddle.y - 0.15f && y - radius < rightPaddle.y + 0.15f) {
        dx = -constantSpeed; // Bounce left with constant speed

        // Adjust dy based on collision point, limit the maximum angle
        float hitPoint = (y - rightPaddle.y) / (0.15f * 2); // Normalize hit point to [-0.5, 0.5]
        dy = constantSpeed * hitPoint; // Adjust vertical direction based on hit point
    }

    // Normalize the velocity to maintain the constant speed after collision adjustment
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        dx = (dx / length) * constantSpeed;
        dy = (dy / length) * constantSpeed;
    }
}

void Ball::draw() const {
    const float segments = 32.0f;
    const float increment = 2.0f * static_cast<float>(M_PI) / segments;
    float angle = 0.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of circle
    for (int i = 0; i <= segments; i++) {
        glVertex2f(x + (radius * cosf(angle)), y + (radius * sinf(angle)));
        angle += increment;
    }
    glEnd();
}

void Ball::resetPosition() {
    x = 0.0f; // Center position
    y = 0.0f; // Center position
    dx = 0.0f; // Stop horizontal movement
    dy = 0.0f; // Stop vertical movement
    canMove = false; // Prevents the ball from moving until space bar is pressed again
}


