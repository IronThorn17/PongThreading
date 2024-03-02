// game.cpp
#include "Game.h"
#include "ball.h"
#include "paddle.h"
#include <stdexcept>
#include <iostream>
#include <GLFW/glfw3.h>

// Screen Variables
int Game::screenW = 1200;
int Game::screenH = 800;

// Left Paddle Variables
float leftPaddleX = -0.95f;
float leftPaddleY = 0.0f;
float leftPaddleW = 0.03f;
float leftPaddleH = 0.3f;
float leftPaddleS = 0.01f;

// Right Paddle Variables
float rightPaddleX = 0.95f;
float rightPaddleY = 0.0f;
float rightPaddleW = 0.03f;
float rightPaddleH = 0.3f;
float rightPaddleS = 0.01f;

// Ball Variables
float ballX = 0.0f;
float ballY = 0.0f;
float ballR = 0.02f;
float ballS = 0.3f;

bool startGame = true;

Game::Game()
    : leftPaddle(leftPaddleX, leftPaddleY, leftPaddleW, leftPaddleH, leftPaddleS),
      rightPaddle(rightPaddleX, rightPaddleY, rightPaddleW, rightPaddleH, rightPaddleS),
      ball(ballX, ballY, ballR, ballS) {


    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    window = glfwCreateWindow(screenW, screenH, "Pong Threading", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    // Continue with the rest of your initialization...

    // Example: Print OpenGL version
    const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else {
        std::cerr << "Failed to retrieve OpenGL version" << std::endl;
    }
}

Game::~Game() {
    // Destructor definition
    // Clean up resources if needed
    glfwTerminate();
}

GLFWwindow* Game::getWindow() const {
    return window;
}

void Game::run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        update();
        render();
    }
}

// Implement other member functions (processInput, update, render)...


void Game::processInput() {
    // Moves paddles
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        leftPaddle.moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        leftPaddle.moveDown();
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        rightPaddle.moveUp();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        rightPaddle.moveDown();
    }

    // Moves ball
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && startGame) {
        ball.startMoving();
        startGame = false;
    }
}

void Game::update() {
    leftPaddle.update();
    rightPaddle.update();
    ball.update();

    // Add game logic such as collision detection, scoring, etc.
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    leftPaddle.draw();
    rightPaddle.draw();
    ball.draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
}
