#ifndef BALL_H
#define BALL_H
#pragma once

#include "paddle.h"
#include "BallLogic.h"
#include <vector>
#include <utility>

class Game;

class Ball {
public:
    Ball(BallLogic& logic,const Paddle& leftPaddle, const Paddle& rightPaddle);

    void update(float deltaTime);
    void startMoving();
    void draw() const;

    void handleScreenCollisions();
    void handlePaddleCollisions();

private:
    void handleSinglePaddleCollision(const Paddle& paddle, int directionModifier);

    BallLogic& logic;

    const Paddle& leftPaddle;
    const Paddle& rightPaddle;
};
#endif