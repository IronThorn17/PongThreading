// Ensure this header is only included once by the preprocessor in a single compilation
#pragma once

// Guard to prevent the multiple inclusion of this header file
#ifndef PADDLE_H
#define PADDLE_H

#include <mutex>
#include <thread>

// Declaration of the Paddle class
class Paddle {
public:
    // Variables to store the paddle's position on the screen
    float x, y;
    // Variable to store the speed at which the paddle moves
    float speed;
    // Booleans to determine whether the paddle is moving up or down
    bool up, down;

    // Constructor for the paddle, takes initial position as parameters
    Paddle(float posX, float posY);
    // Destructor for the paddle
    ~Paddle();
    // Method to update the paddle's position based on the current movement flags
    void update();
    // Method to draw the paddle on the screen
    void draw() const;
    void updateLoop();

private:
    std::mutex mutex;
    std::thread updateThread;
};

// End of the include guard
#endif


