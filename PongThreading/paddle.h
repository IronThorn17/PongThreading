#pragma once
#include "PaddleLogic.h"

class Paddle {
public:
    Paddle(float x, float y, float width, float height, float speed)
    : logic(x, y, width, height, speed) {}

    void draw() const;

    bool tryMoveUp() { return logic.tryMoveUp(); }
    bool tryMoveDown() { return logic.tryMoveDown(); }

    float getX() const { return logic.getX(); }
    float getY() const { return logic.getY(); }
    float getWidth() const { return logic.getWidth(); }
    float getHeight() const { return logic.getHeight(); }

private:
    PaddleLogic logic;
};
