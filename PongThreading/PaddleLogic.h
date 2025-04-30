#pragma once

class PaddleLogic {
public:
    PaddleLogic(float startX, float startY, float width, float height, float speed);

    bool tryMoveUp();
    bool tryMoveDown();

    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getSpeed() const { return speed; }

    static bool canMoveUp(float y, float height, float speed);
    static bool canMoveDown(float y, float height, float speed);
    static float moveUpIfPossible(float y, float height, float speed);
    static float moveDownIfPossible(float y, float height, float speed);

private:
    float x, y;
    float width, height;
    float speed;
};
