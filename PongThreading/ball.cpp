#include "ball.h"
#include "game.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <cstdlib>

Ball::Ball(BallLogic& logic, const Paddle& leftPaddle, const Paddle& rightPaddle)
    : logic(logic),leftPaddle(leftPaddle), rightPaddle(rightPaddle) {}

    void Ball::update(float deltaTime) {
        logic.moveBall();
        handleScreenCollisions();
        handlePaddleCollisions();
    }

    void Ball::startMoving() {
        logic.startMoving();
    }

    void Ball::draw() const {
        const auto vertices = logic.calculateVertices(64, Game::getScreenWidth() / static_cast<float>(Game::getScreenHeight()));
        glBegin(GL_TRIANGLE_FAN);
        for (const auto& vertex : vertices)
            glVertex2f(vertex.first, vertex.second);
        glEnd();
    }


    void Ball::handleScreenCollisions() {
        if (BallLogic::checkTopCollision(logic.getY(), logic.getSize())) {
            logic.setDirection(logic.getDirectionX(), -std::abs(logic.getDirectionY()));
        } else if (BallLogic::checkBottomCollision(logic.getY(), logic.getSize())) {
            logic.setDirection(logic.getDirectionX(), std::abs(logic.getDirectionY()));
        }
    
        if (BallLogic::checkRightScore(logic.getX(), logic.getSize())) {
            // Player 1 scores
        } else if (BallLogic::checkLeftScore(logic.getX(), logic.getSize())) {
            // Player 2 scores
        }
    }

    void Ball::handleScreenCollisions() {
        if (BallLogic::checkTopCollision(logic.getY(), logic.getSize())) {
            logic.setDirection(logic.getDirectionX(), -std::abs(logic.getDirectionY()));
        } else if (BallLogic::checkBottomCollision(logic.getY(), logic.getSize())) {
            logic.setDirection(logic.getDirectionX(), std::abs(logic.getDirectionY()));
        }

        if (BallLogic::checkRightScore(logic.getX(), logic.getSize())) {
            // Player 1 scores
        } else if (BallLogic::checkLeftScore(logic.getX(), logic.getSize())) {
            // Player 2 scores
        }
    }

    void Ball::handlePaddleCollisions() {
        handleSinglePaddleCollision(leftPaddle, -1);
        handleSinglePaddleCollision(rightPaddle, 1);
    }

    void Ball::handleSinglePaddleCollision(const Paddle& paddle, int directionModifier) {
        float ballRadius = logic.getSize();
        float paddleTop = paddle.getY() + (paddle.getHeight() / 2);
        float paddleBottom = paddle.getY() - (paddle.getHeight() / 2);
        float paddleEdge = paddle.getX() + -directionModifier * paddle.getWidth() / 2;

        float ballX = logic.getX();
        float ballY = logic.getY();

        if (ballX + ballRadius >= paddleEdge && ballX - ballRadius <= paddleEdge &&
            ballY + ballRadius >= paddleBottom && ballY - ballRadius <= paddleTop) {

            float portionHit = (ballY - paddle.getY()) / (paddle.getHeight() / 2);

            if (std::abs(ballX - paddleEdge) <= 0.05f) {
                float newDY = logic.getDirectionY();
                if (portionHit > 0.66f) newDY += 0.2f;
                else if (portionHit < -0.66f) newDY -= 0.2f;

                logic.setDirection(-logic.getDirectionX(), newDY);
            }
        }
    }

