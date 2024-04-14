#pragma once // Ensure the header is included only once during compilation

#ifndef GAME_H // Guard against multiple inclusions of the header
#define GAME_H

// Include the definition of the Paddle class
#include "paddle.h"  
// Include the definition of the Ball class
#include "ball.h"    
// Include the GLFW library for handling window operations
#include <GLFW/glfw3.h>  
// Include atomic for managing shared variables in concurrent environments
#include <atomic>    
// Include thread for handling multithreading
#include <thread>    
// Include iostream for input/output operations
#include <iostream>  

// Define the Game class
class Game {
private:
    // Pointer to the GLFW window
    GLFWwindow* window;
    // Object representing the left paddle
    Paddle leftPaddle;
    // Object representing the right paddle
    Paddle rightPaddle;
    // Atomic boolean to manage the game's running state across threads
    std::atomic<bool> isRunning;
    // Thread for handling input separately
    std::thread inputThread;
    // Object representing the game ball
    Ball ball;
    // Flag to check if the ball movement has started
    bool ballStarted;
    // Scores for player 1 and player 2
    int scoreP1, scoreP2;

    // Method to handle input processing
    void processInput();
    // Static method that runs as a thread to process input continuously
    static void inputLoop(Game* game);
    // Method to update the score based on who scored
    void updateScore(bool leftScored);
    // Method to print the current score to the console
    void printScore() const;

public:
    // Constructor to initialize the game
    Game();
    // Destructor to clean up resources
    ~Game();
    // Method to start the game loop
    void run();
    // Method to stop the game loop
    void stop();
    // Method to update the game state
    void update();
    // Method to handle drawing of game components
    void draw();
};

#endif // End of include guard
