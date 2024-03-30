// Ensure this header is only included once by the preprocessor in a single compilation
#pragma once

// Alternative include guard to prevent multiple inclusions of this header file
#ifndef GAME_H
#define GAME_H

// Include the Paddle and Ball class definitions
#include "paddle.h"
#include "ball.h"
// Include the GLFW library for window management and OpenGL context
#include <GLFW/glfw3.h>
// Include atomic for thread-safe boolean operations
#include <atomic>
// Include thread for managing input in a separate thread
#include <thread>

// Definition of the Game class
class Game {
private:
    // Pointer to the GLFW window for rendering and input handling
    GLFWwindow* window;
    // Instances of Paddle for the left and right paddles in the game
    Paddle leftPaddle;
    Paddle rightPaddle;
    // Atomic boolean flag to safely control the game loop across threads
    std::atomic<bool> isRunning;
    // Thread object for processing input independently of the main game loop
    std::thread inputThread;

    // Instance of Ball for the game ball
    Ball ball;
    // Boolean flag to track whether the ball has started moving
    bool ballStarted;

    // Private method to process input (e.g., paddle movements)
    void processInput();
    // Static method run by the inputThread to continuously check for input
    static void inputLoop(Game* game);

public:
    // Constructor for Game, sets up the game environment
    Game();
    // Destructor for Game, responsible for cleaning up resources
    ~Game();
    // Starts and runs the main game loop
    void run();
    // Stops the game, ending the main loop and input thread
    void stop();
    // Updates the game state, such as moving the ball and checking for collisions
    void update();
    // Renders the game state to the window
    void draw();
};

// End of the alternative include guard
#endif 


