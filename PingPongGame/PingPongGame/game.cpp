#include "game.h"  // Include the header file for the Game class
#include <stdexcept>  // Include standard exceptions library
#include <GLFW/glfw3.h>  // Include the GLFW library for window management and graphics

// Constructor for the Game class
Game::Game()
    : window(nullptr), leftPaddle(-0.9f, 0.0f), rightPaddle(0.9f, 0.0f), ball(), ballStarted(false), isRunning(false), scoreP1(0), scoreP2(0) {

    // Initialize GLFW, throw runtime_error if initialization fails
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Create a window for the game
    window = glfwCreateWindow(640, 480, "Ping Pong Game", nullptr, nullptr);
    if (!window) {
        glfwTerminate();  // Terminate GLFW if window creation fails
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Set the current context to the newly created window
    glfwMakeContextCurrent(window);

    // Set the viewport size based on the framebuffer size of the window
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);  // Set viewport dimensions
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the clear color to black
}

// Destructor for the Game class
Game::~Game() {
    stop();  // Stop the game processes
    if (inputThread.joinable()) {
        inputThread.join();  // Ensure the input thread has completed
    }
    glfwDestroyWindow(window);  // Destroy the window
    glfwTerminate();  // Terminate GLFW
}

// Starts the main game loop
void Game::run() {
    printScore();  // Display initial scores
    isRunning = true;
    inputThread = std::thread(&Game::inputLoop, this);  // Start the input thread

    // Game loop
    while (!glfwWindowShouldClose(window) && isRunning) {
        processInput();  // Handle user input
        update();  // Update game state
        draw();  // Render the game
        glfwSwapBuffers(window);  // Swap the front and back buffers
        glfwPollEvents();  // Poll for and process events
    }

    stop();  // Stop the game
}

// Sets the game running state to false
void Game::stop() {
    isRunning = false;
}

// Updates the state of the game objects
void Game::update() {
    leftPaddle.update();  // Update the left paddle position
    rightPaddle.update();  // Update the right paddle position

    // Check and handle ball movement
    if (ballStarted && ball.canMove) {
        ball.update(leftPaddle, rightPaddle);
    }

    // Check for ball crossing the left boundary
    if (ball.x - ball.radius < -1.0f) {
        updateScore(false);  // P2 scores
        ball.canMove = false;
        ballStarted = false;
    }
    // Check for ball crossing the right boundary
    else if (ball.x + ball.radius > 1.0f) {
        updateScore(true);  // P1 scores
        ball.canMove = false;
        ballStarted = false;
    }
}

// Renders the game objects
void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    leftPaddle.draw();  // Draw the left paddle
    rightPaddle.draw();  // Draw the right paddle
    ball.draw();  // Draw the ball
}

// Processes user input
void Game::processInput() {
    // Handle paddle movement based on key presses
    leftPaddle.up = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    leftPaddle.down = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    rightPaddle.up = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
    rightPaddle.down = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;

    // Start ball movement on SPACE key press
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !ballStarted) {
        ball.startMovement();
        ballStarted = true;
        ball.canMove = true;
    }
}

// Updates the score based on which player scored
void Game::updateScore(bool leftScored) {
    if (leftScored) {
        scoreP1++;  // Increment P1's score
    }
    else {
        scoreP2++;  // Increment P2's score
    }
    ball.resetPosition();  // Reset the ball position
    printScore();  // Print the updated scores
}

// Prints the current score to the console
void Game::printScore() const {
    // Clear the console screen based on the operating system
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
    std::cout << "P1 is Green --- P2 is Yellow" << std::endl;  // Output color information
    std::cout << "P1 Score: " << scoreP1 << " | P2 Score: " << scoreP2 << std::endl;  // Output the scores
}

// Input loop to continuously process input while the game is running
void Game::inputLoop(Game* game) {
    while (game->isRunning) {
        game->processInput();  // Process input continuously
    }
}
