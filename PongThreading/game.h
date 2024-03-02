// game.h
#pragma once

#include <GLFW/glfw3.h>
#include "Paddle.h"
#include "Ball.h"

class Game {
public:
    Game();
    ~Game();
    void run();

    GLFWwindow* getWindow() const;
    static int getScreenWidth() { return screenW; }
    static int getScreenHeight() { return screenH; }

private:
    GLFWwindow* window;
    Paddle leftPaddle, rightPaddle;
    Ball ball;

    void processInput();
    void update();
    void render();

    static int screenW;
    static int screenH;
};
