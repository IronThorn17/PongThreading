#pragma once

#ifndef PADDLE_H
#define PADDLE_H

class Paddle {
public:
    float x, y; // Paddle position
    float speed; // Speed of the paddle movement
    bool up, down; // Movement flags

    Paddle(float posX, float posY);
    void update();
    void draw() const;
};

#endif // PADDLE_H

