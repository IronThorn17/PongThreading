#include "ball.h"  // Include the header for the Ball class
#include "paddle.h"  // Include the header for the Paddle class
#include <GLFW/glfw3.h>  // Include the GLFW library for window management and graphics
#include <cmath>  // Include the C++ mathematical library
#include <cstdlib>  // Include the C++ standard library for general utilities
#include <ctime>  // Include the C++ library for time functions

// Define M_PI if it's not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Ball constructor with initial state settings
Ball::Ball() : x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), radius(0.02f), canMove(false) {}

// Initializes ball movement
void Ball::startMovement() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Determine random initial horizontal direction
    int direction = (std::rand() % 2) * 2 - 1; // Generates either -1 or 1

    // Set horizontal and vertical speeds
    dx = 0.0003f * direction; // Set horizontal velocity
    dy = 0.0f; // Initially no vertical velocity

    // Allow the ball to start moving
    canMove = true;
}

// Updates the position and state of the ball
void Ball::update(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    if (!canMove) return; // Do nothing if movement is not allowed

    // Update ball position based on velocity
    x += dx;
    y += dy;

    // Invert vertical direction if ball hits the top or bottom of the screen
    if (y + radius >= 1.0f || y - radius <= -1.0f) {
        dy = -dy; // Reverse vertical direction
    }

    // Handle collisions with paddles
    handlePaddleCollision(leftPaddle, rightPaddle);
}

// Resets the ball to the center of the screen
void Ball::resetPosition() {
    x = 0.0f; // Center horizontally
    y = 0.0f; // Center vertically
    dx = 0.0f; // No horizontal velocity
    dy = 0.0f; // No vertical velocity
    canMove = false; // Disable movement
}

// Checks for and handles collisions with paddles
void Ball::handlePaddleCollision(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    // Compute the speed of the ball to maintain after collisions
    const float constantSpeed = std::sqrt(dx * dx + dy * dy); // Calculate the magnitude of velocity

    // Check for collision with the left paddle
    if (x - radius < leftPaddle.x + 0.02f && x + radius > leftPaddle.x - 0.02f &&
        y + radius > leftPaddle.y - 0.15f && y - radius < leftPaddle.y + 0.15f) {
        dx = constantSpeed; // Set horizontal speed to right

        // Calculate vertical bounce effect based on collision point
        float hitPoint = (y - leftPaddle.y) / (0.15f * 2);
        dy = constantSpeed * hitPoint;
    }

    // Check for collision with the right paddle
    if (x + radius > rightPaddle.x - 0.02f && x - radius < rightPaddle.x + 0.02f &&
        y + radius > rightPaddle.y - 0.15f && y - radius < rightPaddle.y + 0.15f) {
        dx = -constantSpeed; // Set horizontal speed to left

        // Calculate vertical bounce effect based on collision point
        float hitPoint = (y - rightPaddle.y) / (0.15f * 2);
        dy = constantSpeed * hitPoint;
    }

    // Normalize the speed to maintain constant speed after collision
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        dx = (dx / length) * constantSpeed;
        dy = (dy / length) * constantSpeed;
    }
}

// Renders the ball as a circle using OpenGL
void Ball::draw() const {
    const float segments = 32.0f; // Define number of segments for the circle approximation
    const float increment = 2.0f * static_cast<float>(M_PI) / segments; // Compute angle increment
    float angle = 0.0f;

    // Begin drawing the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Start from the center
    for (int i = 0; i <= segments; i++) {
        // Add vertices to form the circle
        glVertex2f(x + (radius * cosf(angle)), y + (radius * sinf(angle)));
        angle += increment; // Increment the angle
    }
    glEnd(); // Finish drawing
}



