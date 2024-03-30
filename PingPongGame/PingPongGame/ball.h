// Ensure this header file is included only once in a single compilation
#pragma once

// Alternative include guard to prevent multiple inclusions of this header file
#ifndef BALL_H
#define BALL_H

// Include the definition of the Paddle class
#include "paddle.h"

// Definition of the Ball class
class Ball {
public:
    // Variables for storing the ball's current position
    float x, y;
    // Variables for storing the ball's movement in the x and y directions
    float dx, dy;
    // Variable for storing the ball's radius
    float radius;
    // Boolean flag to control whether the ball is allowed to move
    bool canMove;

    // Constructor declaration; initializes a new instance of the Ball class
    Ball();
    // Method to start the ball's movement
    void startMovement();
    // Method to update the ball's position based on paddle positions
    void update(const Paddle& leftPaddle, const Paddle& rightPaddle);
    // Method to draw the ball on the screen
    void draw() const;
    // Method to reset the ball to its initial position
    void resetPosition();

private:
    // Helper method to handle collisions with the paddles
    void handlePaddleCollision(const Paddle& leftPaddle, const Paddle& rightPaddle);
};

// End of the alternative include guard
#endif 