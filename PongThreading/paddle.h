#pragma once

class Paddle {
public:
    Paddle(float startX, float startY, float width, float height, float speed);

    // Public movement functions for runtime
    bool tryMoveUp();
    bool tryMoveDown();

    // Rendering
    void draw() const;

    // Getters for testing
    float getX() const { return x; }
    float getY() const { return y; }
    float getWidth() const { return width; }
    float getHeight() const { return height; }
    float getSpeed() const { return speed; }

    // Static versions for testing logic independently
    static bool canMoveUp(float y, float height, float speed);
    static bool canMoveDown(float y, float height, float speed);
    static float moveUpIfPossible(float y, float height, float speed);
    static float moveDownIfPossible(float y, float height, float speed);

private:
    float x, y;
    float width, height;
    float speed;
};
