// Include the definition of the Game class to be able to use it
#include "game.h"
// Include the iostream library for input/output operations, specifically for error reporting
#include <iostream>

// The entry point of the application
int main() {
    try {
        // Create an instance of the Game class
        Game game;
        // Start the game loop
        game.run();
    }
    // Catch and handle any exceptions that are thrown within the try block
    catch (const std::exception& e) {
        // Output the error message to the standard output
        std::cout << e.what() << std::endl;
        // Return -1 to indicate that the program terminated with an error
        return -1;
    }
    // Return 0 to indicate that the program terminated without any errors
    return 0;
}

