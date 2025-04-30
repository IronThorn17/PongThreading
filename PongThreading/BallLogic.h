#pragma once
#include <vector>
#include <utility>

class BallLogic {
public:
    BallLogic(float startX, float startY, float size, float speed);

    void startMoving();
    void moveBall(float deltaTime);

    void setDirection(float dx, float dy);
    void setPosition(float newX, float newY);
    void setCanMove(bool moving);
    void setSpeed(float newSpeed);

    float getX() const;
    float getY() const;
    float getDirectionX() const;
    float getDirectionY() const;
    float getSize() const;
    bool isMoving() const;
    

    std::pair<float, float> computeNextPosition(float deltaTime) const;

    static bool checkTopCollision(float y, float radius);
    static bool checkBottomCollision(float y, float radius);
    static bool checkLeftScore(float x, float radius);
    static bool checkRightScore(float x, float radius);

    std::vector<std::pair<float, float>> calculateVertices(int segments = 64, float aspectRatio = 1.5f) const;

private:
    float x, y;
    float size;
    float speed;
    float directionX, directionY;
    bool canMove;
};
