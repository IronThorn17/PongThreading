#pragma once

#ifndef GAME_H
#define GAME_H

#include "paddle.h"
#include "ball.h"
#include <GLFW/glfw3.h>
#include <atomic>
#include <thread>

class Game {
private:
    GLFWwindow* window;
    Paddle leftPaddle;
    Paddle rightPaddle;
    std::atomic<bool> isRunning;
    std::thread inputThread;

    Ball ball;
    bool ballStarted;

    void processInput();
    static void inputLoop(Game* game);

public:
    Game();
    ~Game();
    void run();
    void stop();
    void update();
    void draw();
};

#endif // GAME_H

