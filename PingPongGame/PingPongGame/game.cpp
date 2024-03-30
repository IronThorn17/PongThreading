// Include the Game class definition
#include "game.h"
// Include the standard exception library for throwing runtime errors
#include <stdexcept> 
// Include GLFW for window management and OpenGL context
#include <GLFW/glfw3.h> 

// Constructor for the Game class
Game::Game()
    : window(nullptr), // Initialize the GLFWwindow pointer to nullptr
    leftPaddle(-0.9f, 0.0f), // Initialize left paddle at the left side of the screen
    rightPaddle(0.9f, 0.0f), // Initialize right paddle at the right side of the screen
    ball(), // Default-initialize the ball
    ballStarted(false), // Initially, the ball is not moving
    isRunning(false) { // The game loop is not running yet

    // Initialize GLFW library
    if (!glfwInit()) {
        // If initialization fails, throw a runtime error
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Create a GLFW window with given dimensions and title
    window = glfwCreateWindow(640, 480, "Ping Pong Game", nullptr, nullptr);
    if (!window) {
        // If window creation fails, terminate GLFW and throw a runtime error
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the created window's OpenGL context current
    glfwMakeContextCurrent(window);

    // Set the OpenGL viewport based on the window's framebuffer size
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set the OpenGL clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Destructor for the Game class
Game::~Game() {
    stop(); // Stop the game if it's running
    if (inputThread.joinable()) {
        // If the input thread is running, join it (wait for it to finish)
        inputThread.join();
    }
    // Clean up: destroy the window and terminate GLFW
    glfwDestroyWindow(window);
    glfwTerminate();
}

// Method to start and run the game loop
void Game::run() {
    isRunning = true; // Mark the game as running
    // Start the input handling in a separate thread
    inputThread = std::thread(&Game::inputLoop, this);

    // Main game loop: runs until the window is closed or the game is stopped
    while (!glfwWindowShouldClose(window) && isRunning) {
        processInput(); // Process user input
        update(); // Update game objects
        draw(); // Draw the game objects to the window
        // Swap the front and back buffers (double buffering)
        glfwSwapBuffers(window);
        // Poll for and process events (e.g., keyboard and mouse events)
        glfwPollEvents();
    }

    // Once the loop ends, ensure the game is properly stopped
    stop();
}

// Method to stop the game
void Game::stop() {
    isRunning = false; // Mark the game as not running
}

// Method to update game objects each frame
void Game::update() {
    // Update the positions of the paddles
    leftPaddle.update();
    rightPaddle.update();

    // If the ball has been started, update its position
    if (ballStarted) {
        ball.update(leftPaddle, rightPaddle);
        // If the ball cannot move (e.g., it was reset), prepare it for restarting
        if (!ball.canMove) {
            ballStarted = false; // Ready to start the ball again
        }
    }
}

// Method to draw the game objects to the window
void Game::draw() {
    // Clear the window with the clear color set in the constructor
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the paddles and the ball
    leftPaddle.draw();
    rightPaddle.draw();
    ball.draw(); // Always draw the ball, even if it hasn't been started
}

// Method to process user input
void Game::processInput() {
    // Update paddle movement based on keyboard input
    leftPaddle.up = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    leftPaddle.down = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    rightPaddle.up = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    rightPaddle.down = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;

    // Start the ball movement if the spacebar is pressed and the ball is not already moving
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !ballStarted && !ball.canMove) {
        ball.startMovement(); // Initiate ball movement
        ballStarted = true; // Mark the ball as started
    }
}

// Static method as the entry point for the input thread
void Game::inputLoop(Game* game) {
    // Continuously process input while the game is running
    while (game->isRunning) {
        game->processInput();
    }
}
