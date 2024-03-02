#pragma once

class Paddle {
public:
    Paddle(float startX, float startY, float width, float height, float speed);
    void moveUp();
    void moveDown();
    void update();
    void draw();
    float x, y, width, height, speed;

private:

};

