#include <iostream>  // Include this header for std::cerr and std::endl
#include <cstdlib>   // Include this header for EXIT_FAILURE and EXIT_SUCCESS
#include "Game.h"

int main() {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        // Handle any exceptions that might occur during initialization
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
