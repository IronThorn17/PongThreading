#include "game.h"
#include <stdexcept> // Make sure to include this for std::runtime_error
#include <GLFW/glfw3.h> // Ensure GLFW is included

Game::Game()
    : window(nullptr),
    leftPaddle(-0.9f, 0.0f),
    rightPaddle(0.9f, 0.0f),
    ball(),
    ballStarted(false),
    isRunning(false) {

    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    // Create a GLFWwindow object
    window = glfwCreateWindow(640, 480, "Ping Pong Game", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the viewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Set clear color to black (OpenGL's default)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Game::~Game() {
    stop();
    if (inputThread.joinable()) {
        inputThread.join();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Game::run() {
    isRunning = true;
    inputThread = std::thread(&Game::inputLoop, this);

    while (!glfwWindowShouldClose(window) && isRunning) {
        processInput();
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    stop();
}

void Game::stop() {
    isRunning = false;
}

void Game::update() {
    leftPaddle.update();
    rightPaddle.update();

    if (ballStarted) {
        ball.update(leftPaddle, rightPaddle);
        // Check if ball has hit the left or right side
        if (ball.x + ball.radius > 1.0f || ball.x - ball.radius < -1.0f) {
            ball.resetPosition();
            ballStarted = false; // Allow the ball to be started again with the space bar
        }
    }
}


void Game::draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    leftPaddle.draw();
    rightPaddle.draw();

    // Always draw the ball regardless of ballStarted status
    ball.draw();
}

void Game::processInput() {
    leftPaddle.up = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    leftPaddle.down = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    rightPaddle.up = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    rightPaddle.down = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;

    // Start the ball movement on spacebar press
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !ballStarted) {
        ball.startMovement(); // Initiates ball movement
        ballStarted = true; // Ensures this block won't be entered again until the game is reset or restarted
    }
}

void Game::inputLoop(Game* game) {
    while (game->isRunning) {
        game->processInput();
    }
}
