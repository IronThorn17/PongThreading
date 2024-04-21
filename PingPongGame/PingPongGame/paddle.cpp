#include "paddle.h"
#include <GLFW/glfw3.h>
#include <thread>

Paddle::Paddle(float posX, float posY) : x(posX), y(posY), speed(0.005f), up(false), down(false) {
    // Start the update thread
    updateThread = std::thread(&Paddle::updateLoop, this);
}

Paddle::~Paddle() {
    // Join the update thread if it's joinable
    if (updateThread.joinable()) {
        updateThread.join();
    }
}

void Paddle::update() {
    // If moving up and not at the upper boundary, increase the y position
    if (up && y < 1 - 0.15f) y += speed; // Ensure paddle stays within the upper boundary
    // If moving down and not at the lower boundary, decrease the y position
    if (down && y > -1 + 0.15f) y -= speed; // Ensure paddle stays within the lower boundary
}

void Paddle::updateLoop() {
    while (true) {
        // Acquire lock to ensure thread safety
        std::lock_guard<std::mutex> lock(mutex);

        // Update paddle position based on movement flags
        if (up && y < 1 - 0.15f) y += speed;
        if (down && y > -1 + 0.15f) y -= speed;

        // Release lock

        // Add a small delay to control the update frequency
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Paddle::draw() const {
    if (x < 0) {
        // Left paddle, set color to green
        glColor3f(0.0f, 1.0f, 0.0f); // RGB for green
    }
    else {
        // Right paddle, set color to yellow
        glColor3f(1.0f, 1.0f, 0.0f); // RGB for yellow
    }

    glBegin(GL_QUADS); // Start drawing a quad
    glVertex2f(x - 0.02f, y - 0.15f); // Bottom left
    glVertex2f(x + 0.02f, y - 0.15f); // Bottom right
    glVertex2f(x + 0.02f, y + 0.15f); // Top right
    glVertex2f(x - 0.02f, y + 0.15f); // Top left
    glEnd(); // End drawing

    // Reset color to white for other objects
    glColor3f(1.0f, 1.0f, 1.0f);
}
