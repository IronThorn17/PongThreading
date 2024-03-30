// Include the header for the Ball class to ensure class definition is available
#include "Ball.h"
// Include the header for the Paddle class to use it for collision detection
#include "paddle.h"
// Include the GLFW library for creating windows and managing user inputs
#include <GLFW/glfw3.h>
// Include cmath for access to the square root and trigonometric functions
#include <cmath>
// Include cstdlib for random number generation functions std::rand() and std::srand()
#include <cstdlib>
// Include ctime for the current time to seed the random number generator with std::time()
#include <ctime>

// Define M_PI for the value of Pi if it is not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constructor initializing the ball with default values: position at origin, no movement, and a small radius
Ball::Ball() : x(0.0f), y(0.0f), dx(0.0f), dy(0.0f), radius(0.02f), canMove(false) {}

// Start movement of the ball by determining a random direction and setting initial velocity
void Ball::startMovement() {
    // Seed the random number generator with current time
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Randomly choose the direction to be either left (-1) or right (1) for horizontal movement
    int direction = (std::rand() % 2) * 2 - 1; // Generates either -1 or 1

    dx = 0.0005f * direction; // Set the horizontal velocity in the chosen direction
    dy = 0.0f; // Initially, there is no vertical movement

    canMove = true; // Enable movement for the ball
}

// Update the position and behavior of the ball each frame, considering collisions
void Ball::update(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    if (!canMove) return; // Do not update if movement is disabled

    // Update ball's position based on its velocity
    x += dx;
    y += dy;

    // Invert vertical velocity if colliding with the top or bottom of the screen
    if (y + radius >= 1.0f || y - radius <= -1.0f) {
        dy = -dy;
    }

    // Reset ball position if it passes beyond the left or right bounds of the screen
    if (x + radius > 1.0f || x - radius < -1.0f) {
        resetPosition();
    }

    // Check and handle collisions with the paddles
    handlePaddleCollision(leftPaddle, rightPaddle);
}

// Handle collision of the ball with either paddle
void Ball::handlePaddleCollision(const Paddle& leftPaddle, const Paddle& rightPaddle) {
    // Calculate the constant speed of the ball for consistent movement after collisions
    const float constantSpeed = std::sqrt(dx * dx + dy * dy);

    // Handle collision with the left paddle
    if (x - radius < leftPaddle.x + 0.02f && x + radius > leftPaddle.x - 0.02f &&
        y + radius > leftPaddle.y - 0.15f && y - radius < leftPaddle.y + 0.15f) {
        dx = constantSpeed; // Move right at constant speed post-collision

        // Adjust vertical velocity based on where the ball hit the paddle, to control the angle of reflection
        float hitPoint = (y - leftPaddle.y) / (0.15f * 2); // Normalize hit point to range [-0.5, 0.5]
        dy = constantSpeed * hitPoint; // Adjust vertical direction based on hit point
    }

    // Handle collision with the right paddle
    if (x + radius > rightPaddle.x - 0.02f && x - radius < rightPaddle.x + 0.02f &&
        y + radius > rightPaddle.y - 0.15f && y - radius < rightPaddle.y + 0.15f) {
        dx = -constantSpeed; // Move left at constant speed post-collision

        // Similar adjustment for the vertical velocity as with the left paddle collision
        float hitPoint = (y - rightPaddle.y) / (0.15f * 2);
        dy = constantSpeed * hitPoint;
    }

    // Normalize the ball's velocity to maintain constant speed after adjusting for collision impact
    float length = std::sqrt(dx * dx + dy * dy);
    if (length != 0) {
        dx = (dx / length) * constantSpeed;
        dy = (dy / length) * constantSpeed;
    }
}

// Draw the ball on the screen as a filled circle
void Ball::draw() const {
    const float segments = 32.0f; // Number of line segments to use for the circle
    const float increment = 2.0f * static_cast<float>(M_PI) / segments; // Angle between segments
    float angle = 0.0f;

    // Start drawing a triangle fan to form a circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center of the circle
    for (int i = 0; i <= segments; i++) {
        // Calculate x and y coordinates of the segment endpoint and add it to the fan
        glVertex2f(x + (radius * cosf(angle)), y + (radius * sinf(angle)));
        angle += increment; // Move to the next segment
    }
    glEnd(); // End drawing
}

// Reset the ball to the center of the screen and stop its movement
void Ball::resetPosition() {
    x = 0.0f; // Reset to center horizontally
    y = 0.0f; // Reset to center vertically
    dx = 0.0f; // Stop horizontal movement
    dy = 0.0f; // Stop vertical movement
    canMove = false; // Disable movement until explicitly re-enabled
}



