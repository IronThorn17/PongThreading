// Include the header file for the Paddle class to access its definition
#include "paddle.h"
// Include GLFW for OpenGL functions to draw the paddle
#include <GLFW/glfw3.h>

// Constructor for the Paddle class, initializes a paddle's position, speed, and movement flags
Paddle::Paddle(float posX, float posY) : x(posX), y(posY), speed(0.0005f), up(false), down(false) {}

// Method to update the paddle's position based on current movement flags and boundaries
void Paddle::update() {
    // If moving up and not at the upper boundary, increase the y position
    if (up && y < 1 - 0.15f) y += speed; // Ensure paddle stays within the upper boundary
    // If moving down and not at the lower boundary, decrease the y position
    if (down && y > -1 + 0.15f) y -= speed; // Ensure paddle stays within the lower boundary
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
