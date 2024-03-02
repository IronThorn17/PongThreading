#include "Ball.h"
#include "game.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>

Ball::Ball(float startX, float startY, float size, float speed)
    : x(startX), y(startY), size(size), speed(speed), directionX(1.0f), directionY(1.0f) {}

void Ball::update() {
    Ball::moveBall();
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
    if (y + size >= Game::getScreenHeight()) {
        // Reverse the direction (simulate bounce)
        directionY = -std::abs(directionY);
    }
    else if (y - size <= Game::getScreenHeight()) {
        directionX = -std::abs(directionX);
    }

    if (x <= Game::getScreenWidth()) {
        //glfwSetWindowShouldClose(game.getWindow(), GLFW_TRUE);
    }


    // Check for collision with the sides of the screen
    if (y - size <= 0) {
        // End the game or take appropriate action
        // For now, let's close the game window
        //glfwSetWindowShouldClose(Game::getWindow(), GLFW_TRUE);
    }
}