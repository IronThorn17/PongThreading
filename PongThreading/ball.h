#pragma once

class Ball {
public:
    Ball(float startX, float startY, float size, float speed);
    void update();
    void draw();
    void startMoving();
    void moveBall();
    void handleScreenCollisions();

private:
    float x, y, size, speed;
    float directionX, directionY;
    bool canMove;
};
